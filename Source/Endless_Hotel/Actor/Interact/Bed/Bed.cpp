// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Bed/Bed.h"
#include "GameSystem/SubSystem/EHGameSystem.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include "Player/Character/EHPlayer.h"
#include <Kismet/GameplayStatics.h>

#pragma region Base

ABed::ABed(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Comp_Direction = CreateDefaultSubobject<UBedDirectionComponent>(TEXT("Comp_Direction"));
}

void ABed::BeginPlay()
{
	Super::BeginPlay();

	auto* GameSystem = GetGameInstance()->GetSubsystem<UEHGameSystem>();
	GameSystem->OnProgressionChanged.AddUObject(this, &ThisClass::OnChangedProgression);

	bool bActive = GameSystem->GetGameProgression() == EGameProgression::CheckIn;
	Component_Interact->ActiveInteract(bActive);

	auto* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->OnRevive.AddWeakLambda(this, [this]() {StartWakeUp(AM_BriefWakeUp, true); });

	auto* FloorSub = GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>();
	if (GameSystem->GetGameProgression() != EGameProgression::CheckIn && FloorSub->GetIsFirstFloor())
	{
		bool bGameClear = GameSystem->IsGameClear();
		UAnimMontage* TargetMontage = bGameClear ? AM_BriefWakeUp : AM_WakeUp;
		StartWakeUp(TargetMontage, bGameClear);
	}
}

void ABed::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	auto* GameSystem = GetGameInstance()->GetSubsystem<UEHGameSystem>();
	if (IsValid(GameSystem))
	{
		GameSystem->OnProgressionChanged.RemoveAll(this);
	}

	auto* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(Player))
	{
		Player->OnRevive.RemoveAll(this);
	}

	Super::EndPlay(EndPlayReason);
}

#pragma endregion

#pragma region Interact

void ABed::Interact(AEHCharacter* Interacter)
{
	Super::Interact(Interacter);

	FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();
	switch (Info.InteractType)
	{
	case EInteractType::Rest:
		StartRest();
		break;
	}
}

#pragma endregion

#pragma region Progression

void ABed::OnChangedProgression(EGameProgression Target)
{
	bool bActive = Target == EGameProgression::CheckIn;
	Component_Interact->ActiveInteract(bActive);
}

#pragma endregion

#pragma region Rest

void ABed::StartRest()
{
	Comp_Direction->SyncCameraRotation(true);
	Comp_Direction->SetPlayerInputAble(false);

	auto* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PC->SetControlRotation(RestTrans.Rotator());

	auto* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->SetActorTransform(RestTrans);
	Player->SetControlRotation(false);
	Player->SetCameraRotation(FRotator(0, 90, -90));
	Player->PlayAnimMontage(AM_Rest);

	const float EyeDelay = 10.5f;
	FTimerHandle EyeHandle;
	GetWorld()->GetTimerManager().SetTimer(EyeHandle, FTimerDelegate::CreateUObject(Comp_Direction, &UBedDirectionComponent::ShowEyeEffect, false), EyeDelay, false);

	const float WakeUpDelay = EyeDelay + 8.f;
	FTimerHandle WakeUpHandle;
	GetWorld()->GetTimerManager().SetTimer(WakeUpHandle, FTimerDelegate::CreateUObject(this, &ThisClass::StartWakeUp, AM_WakeUp.Get(), false), WakeUpDelay, false);
}

void ABed::StartWakeUp(UAnimMontage* TargetMontage, bool bFast)
{
	auto* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PC->SetControlRotation(WakeUpTrans.Rotator());

	auto* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->SetActorTransform(WakeUpTrans);
	Player->SetControlRotation(false);
	Player->SetCameraRotation(FRotator(0, 90, -90));
	Player->PlayAnimMontage(TargetMontage);

	bFast ? Comp_Direction->ShowEyeFastEffect() : Comp_Direction->ShowEyeEffect(true);
	
	Comp_Direction->SyncCameraRotation(true);
	Comp_Direction->SetPlayerInputAble(false);

	auto* GameSystem = GetGameInstance()->GetSubsystem<UEHGameSystem>();
	if (GameSystem->GetGameProgression() == EGameProgression::CheckIn)
	{
		GameSystem->ChangeProgression(EGameProgression::Tutorial);
	}

	const float InputDelay = TargetMontage->GetPlayLength() - 0.1f;
	FTimerHandle InputHandle;
	GetWorld()->GetTimerManager().SetTimer(InputHandle, FTimerDelegate::CreateWeakLambda(this, [this, Player, PC]()
		{
			Comp_Direction->SyncCameraRotation(false);
			Comp_Direction->SetPlayerInputAble(true);

			Player->SetActorTransform(EndTrans);
			PC->SetControlRotation(EndTrans.Rotator());
			Player->SetControlRotation(true);
		}), InputDelay, false);
}

#pragma endregion