// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Read/Manual/Manual.h"
#include "GameSystem/SaveGame/SaveManager.h"
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
}

#pragma endregion

#pragma region Interact

void AManual::Interact_Implementation(AEHCharacter* Interacter)
{
	Super::Interact_Implementation(Interacter);

	auto Data = USaveManager::LoadData_Tutorial();
	Data.bReadManual = true;

	USaveManager::SaveData_Tutorial(Data);
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