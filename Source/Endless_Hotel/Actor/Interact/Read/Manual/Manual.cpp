// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Read/Manual/Manual.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include "GameSystem/SubSystem/AnomalyPoolSubsystem.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include "GameSystem/Enum/EnumConverter.h"
#include "Component/Tutorial/TutorialComponent.h"
#include "UI/Controller/UI_Controller.h"
#include <Kismet/KismetSystemLibrary.h>

#pragma region Base

AManual::AManual(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Comp_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Comp_Root"));
	SetRootComponent(Comp_Root);

	Object->SetupAttachment(RootComponent);

	SM_Paper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Paper"));
	SM_Paper->SetupAttachment(RootComponent);
}

void AManual::BeginPlay()
{
	Super::BeginPlay();

	UpTrans = Object->GetRelativeTransform();
	DownTrans = SM_Paper->GetRelativeTransform();

	const FName FindTag = TEXT("Paper");
	TArray<USceneComponent*> Childs;
	Object->GetChildrenComponents(true, OUT Childs);
	for (auto* Child : Childs)
	{
		if (Child->ComponentHasTag(FindTag))
		{
			Child->SetVisibility(false);
			PaperFragments.Add(EnumConverter::GetEnumFromName<EAnomalyRule>(Child->ComponentTags[2]), Cast<UStaticMeshComponent>(Child));
		}
	}

	SM_Paper->GetChildrenComponents(true, OUT Childs);
	for (auto* Child : Childs)
	{
		if (Child->ComponentHasTag(FindTag))
		{
			Child->SetVisibility(false);
			PaperFragments.Add(EnumConverter::GetEnumFromName<EAnomalyRule>(Child->ComponentTags[2]), Cast<UStaticMeshComponent>(Child));
		}
	}

	ShowUnlockRulePaper();

	auto* PoolSub = GetGameInstance()->GetSubsystem<UAnomalyPoolSubsystem>();
	PoolSub->OnAddAnomalyRule.AddUObject(this, &ThisClass::SetNeedRemind);
	PoolSub->OnAddAnomalyRule.AddUObject(this, &ThisClass::OnAddedNewRule);

	auto* FloorSub = GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>();
	FloorSub->FloorChange_Reset.AddUObject(this, &ThisClass::RemindManual);
}

#pragma endregion

#pragma region Interact

void AManual::Interact(AEHCharacter* Interacter)
{
	Super::Interact(Interacter);

	auto Data = USaveManager::LoadData_Progression();
	if (!Data.bReadManual)
	{
		constexpr float Duration = 0.9f;
		FTimerHandle WidgetHandle;
		GetWorld()->GetTimerManager().SetTimer(WidgetHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
			{
				auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
				UICon->OpenWidget(EWidgetType::PopUp_WrongCheck);
			}), Duration, false);

		Data.bReadManual = true;
		USaveManager::SaveData_Progression(Data);
	}

	auto* Comp_Tutorial = FindComponentByClass<UTutorialComponent>();
	Comp_Tutorial->HideTutorialWidget();
	Comp_Tutorial->HideTutorialWidget();
}

#pragma endregion

#pragma region Rule

void AManual::ShowUnlockRulePaper()
{
	TArray<EAnomalyRule> ActiveRules = USaveManager::LoadData_Progression().ActiveRules;
	for (auto Rule : ActiveRules)
	{
		PaperFragments[Rule]->SetVisibility(true);
	}
}

void AManual::OnAddedNewRule(EAnomalyRule Rule)
{
	auto* PoolSub = GetGameInstance()->GetSubsystem<UAnomalyPoolSubsystem>();
	bool bActive = PoolSub->AnomalyRules.Contains(Rule);
	PaperFragments[Rule]->SetVisibility(bActive);
}

#pragma endregion

#pragma region Switch

void AManual::SwitchPaper()
{
	if (bIsSwitching)
	{
		return;
	}

	bIsSwitching = true;

	UStaticMeshComponent* DownPaper = bFirstPaper ? SM_Paper : Object;

	constexpr float MoveDuration = 0.5f;

	FLatentActionInfo LatentInfo;
	LatentInfo.UUID = __LINE__;
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(DownPaper, MiddleTrans.GetLocation(), MiddleTrans.Rotator(), true, true, MoveDuration, true, EMoveComponentAction::Move, LatentInfo);

	FTimerHandle MoveHandle;
	GetWorld()->GetTimerManager().SetTimer(MoveHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			UStaticMeshComponent* UpPaper = bFirstPaper ? Object : SM_Paper;
			UStaticMeshComponent* MiddlePaper = bFirstPaper ? SM_Paper : Object;

			FLatentActionInfo LatentInfo;
			LatentInfo.UUID = __LINE__;
			LatentInfo.CallbackTarget = this;
			UKismetSystemLibrary::MoveComponentTo(UpPaper, DownTrans.GetLocation(), DownTrans.Rotator(), true, true, MoveDuration, true, EMoveComponentAction::Move, LatentInfo);

			LatentInfo.UUID = __LINE__;
			UKismetSystemLibrary::MoveComponentTo(MiddlePaper, UpTrans.GetLocation(), UpTrans.Rotator(), true, true, MoveDuration, true, EMoveComponentAction::Move, LatentInfo);
		}), MoveDuration, false);

	FTimerHandle InteractHandle;
	GetWorld()->GetTimerManager().SetTimer(InteractHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			bIsSwitching = false;
			bFirstPaper = !bFirstPaper;
		}), MoveDuration * 2, false);
}

#pragma endregion

#pragma region Remind

void AManual::RemindManual()
{
	auto* FloorSub = GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>();
	auto* Comp_Tutorial = FindComponentByClass<UTutorialComponent>();
	if (!bNeedRemind || FloorSub->GetFloor() != STARTFLOOR)
	{
		Comp_Tutorial->HideTutorialWidget();
		Comp_Tutorial->HideTutorialWidget();
		return;
	}

	bNeedRemind = false;

	Comp_Tutorial->ShowTutorialWidgetForce();
}

#pragma endregion