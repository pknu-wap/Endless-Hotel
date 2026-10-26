// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Bed/Bed.h"
#include "Component/Interact/InteractComponent.h"
#include "GameSystem/SubSystem/EHGameSystem.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include "Player/Character/EHPlayer.h"
#include "Player/Controller/EHPlayerController.h"
#include "Player/Camera/EHPlayerCameraManager.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/HUD/InGame/UI_HUD_InGame.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Components/CapsuleComponent.h>

#pragma region Base

void ABed::BeginPlay()
{
	Super::BeginPlay();

	auto* GameSystem = GetGameInstance()->GetSubsystem<UEHGameSystem>();
	GameSystem->OnProgressionChanged.AddUObject(this, &ThisClass::OnChangedProgression);

	bool bActive = GameSystem->GetGameProgression() == EGameProgression::CheckIn;
	Component_Interact->ActiveInteract(bActive);

	Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->OnRevive.AddUObject(this, &ThisClass::StartWakeUp);
	PlayerRoot = Cast<UCapsuleComponent>(Player->GetRootComponent());
	PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));

	auto* FloorSub = GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>();
	if (GameSystem->GetGameProgression() != EGameProgression::CheckIn && FloorSub->GetIsFirstFloor())
	{
		StartWakeUp();
	}
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
	SetPlayerInputAble(false);

	ShowDirection(RestInfo);

	FBedDirectionInfo LastInfo = RestInfo.Top();
	FTimerHandle EyeHandle;
	GetWorld()->GetTimerManager().SetTimer(EyeHandle, FTimerDelegate::CreateUObject(this, &ThisClass::ShowEyeEffect, false), LastInfo.Delay + LastInfo.Duration, false);

	constexpr float WakeUpDelay = 8.f;
	FTimerHandle WakeUpHandle;
	GetWorld()->GetTimerManager().SetTimer(WakeUpHandle, FTimerDelegate::CreateUObject(this, &ThisClass::StartWakeUp), LastInfo.Delay + LastInfo.Duration + WakeUpDelay, false);
}

void ABed::StartWakeUp()
{
	SetPlayerInputAble(false);

	FTransform StartTrans = WakeInfo[0].TargetTrans;
	Player->SetActorTransform(StartTrans);
	PC->SetControlRotation(StartTrans.Rotator());

	ShowEyeEffect(true);

	constexpr float StartDelay = 6.f;
	FTimerHandle StartHandle;
	GetWorld()->GetTimerManager().SetTimer(StartHandle, FTimerDelegate::CreateUObject(this, &ThisClass::ShowDirection, WakeInfo), StartDelay, false);

	FBedDirectionInfo LastInfo = WakeInfo.Top();
	constexpr float InputDelay = 6.f;
	FTimerHandle InputHandle;
	GetWorld()->GetTimerManager().SetTimer(InputHandle, FTimerDelegate::CreateUObject(this, &ThisClass::SetPlayerInputAble, true), LastInfo.Delay + LastInfo.Duration + InputDelay, false);

	auto* GameSystem = GetGameInstance()->GetSubsystem<UEHGameSystem>();
	if (GameSystem->GetGameProgression() == EGameProgression::CheckIn)
	{
		GameSystem->ChangeProgression(EGameProgression::Tutorial);
	}
}

void ABed::SetPlayerInputAble(bool bAble)
{
	PC->SetPlayerInputAble(bAble);
	PlayerRoot->SetEnableGravity(bAble);

	ECollisionEnabled::Type CE = bAble ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision;
	PlayerRoot->SetCollisionEnabled(CE);
}

void ABed::ShowDirection(TArray<FBedDirectionInfo> Infos)
{
	UWorld* World = GetWorld();
	for (const FBedDirectionInfo& Info : Infos)
	{
		FTimerHandle DelayHandle;
		World->GetTimerManager().SetTimer(DelayHandle, FTimerDelegate::CreateWeakLambda(this, [this, Info]()
			{
				FLatentActionInfo LatentInfo;
				LatentInfo.CallbackTarget = this;
				LatentInfo.Linkage = 0;
				LatentInfo.UUID = FMath::RandRange(INT32_MIN, INT32_MAX);
				UKismetSystemLibrary::MoveComponentTo(PlayerRoot.Get(), Info.TargetTrans.GetLocation(), Info.TargetTrans.Rotator(), true, true, Info.Duration, false, EMoveComponentAction::Move, LatentInfo);
				AdjustControllerRotation(Info.TargetTrans.Rotator(), Info.Duration);
			}), Info.Delay, false);
	}
}

void ABed::ShowEyeEffect(bool bOpen)
{
	CameraManager->StartEyeEffect(bOpen);

	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	auto* UI_InGame = Cast<UUI_HUD_InGame>(UICon->GetHUDWidget());
	UI_InGame->StartInGameHUD(bOpen);
}

void ABed::AdjustControllerRotation(const FRotator& TargetRotation, float Duration)
{
	StartControllerRot = PC->GetControlRotation();
	TargetControllerRot = TargetRotation;

	ControllerElapsed = 0.f;
	ControllerDuration = Duration;

	UWorld* World = GetWorld();
	World->GetTimerManager().SetTimer(ControllerHandle, FTimerDelegate::CreateWeakLambda(this, [this, World]()
		{
			ControllerElapsed += World->GetDeltaSeconds();

			const float Alpha = FMath::Clamp(ControllerElapsed / ControllerDuration, 0.f, 1.f);
			const FRotator Rotation = FMath::Lerp(StartControllerRot, TargetControllerRot, Alpha);
			PC->SetControlRotation(Rotation);

			if (Alpha >= 1.f)
			{
				PC->SetControlRotation(TargetControllerRot);
				World->GetTimerManager().ClearTimer(ControllerHandle);
			}
		}), 0.016f, true);
}

#pragma endregion