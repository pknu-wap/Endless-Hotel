// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Bed/Bed.h"
#include "Component/Interact/InteractComponent.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Player/Character/EHPlayer.h"
#include "Player/Controller/EHPlayerController.h"
#include "Player/Camera/EHPlayerCameraManager.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>

#pragma region Base

void ABed::BeginPlay()
{
	Super::BeginPlay();

	bool bActive = USaveManager::LoadData_Progression().Progression == EGameProgression::CheckIn;
	Component_Interact->ActiveInteract(bActive);

	EHPlayer = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
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
		MoveToBedStart();
		break;
	}
}

#pragma endregion

#pragma region Sleep

void ABed::MoveToBedStart()
{
	PC->SetPlayerInputAble(false);

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = TEXT("MoveToBedMiddle");
	LatentInfo.UUID = __LINE__;
	LatentInfo.Linkage = 0;

	constexpr float Duration = 0.5f;
	UKismetSystemLibrary::MoveComponentTo(EHPlayer->GetRootComponent(), Trans_Start.GetLocation(), Trans_Start.Rotator(), false, false, Duration, false, EMoveComponentAction::Move, LatentInfo);
	StartControllerRotation(Trans_Start.Rotator(), Duration);
}

void ABed::MoveToBedMiddle()
{
	FTimerHandle DelayHandle;
	GetWorld()->GetTimerManager().SetTimer(DelayHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			FLatentActionInfo LatentInfo;
			LatentInfo.CallbackTarget = this;
			LatentInfo.ExecutionFunction = TEXT("MoveToBedEnd");
			LatentInfo.UUID = __LINE__;
			LatentInfo.Linkage = 0;

			constexpr float Duration = 1.f;
			UKismetSystemLibrary::MoveComponentTo(EHPlayer->GetRootComponent(), Trans_Middle.GetLocation(), Trans_Middle.Rotator(), false, false, Duration, false, EMoveComponentAction::Move, LatentInfo);
			StartControllerRotation(Trans_Middle.Rotator(), Duration);
		}), 1.0f, false);
}

void ABed::MoveToBedEnd()
{
	CameraManager->StartEyeEffect(false);

	constexpr float Duration = 6.f;
	FTimerHandle WakeUpHandle;
	GetWorld()->GetTimerManager().SetTimer(WakeUpHandle, this, &ThisClass::WakeUp, Duration, false);
}

void ABed::WakeUp()
{
	CameraManager->StartEyeEffect(true);

	FTimerHandle DelayHandle;
	GetWorld()->GetTimerManager().SetTimer(DelayHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			FLatentActionInfo LatentInfo;
			LatentInfo.CallbackTarget = this;
			LatentInfo.ExecutionFunction = TEXT("OnCompletedWakeUp");
			LatentInfo.UUID = __LINE__;
			LatentInfo.Linkage = 0;

			constexpr float Duration = 1.f;
			UKismetSystemLibrary::MoveComponentTo(EHPlayer->GetRootComponent(), Trans_Start.GetLocation(), Trans_Start.Rotator(), false, false, Duration, false, EMoveComponentAction::Move, LatentInfo);
			StartControllerRotation(Trans_Start.Rotator(), Duration);
		}), 4.f, false);
}

void ABed::OnCompletedWakeUp()
{
	PC->SetPlayerInputAble(true);

	FSaveData_Progression Data = USaveManager::LoadData_Progression();
	Data.Progression = EGameProgression::Tutorial;
	USaveManager::SaveData_Progression(Data);
}

void ABed::StartControllerRotation(const FRotator& TargetRotation, float Duration)
{
	StartControllerRot = PC->GetControlRotation();
	TargetControllerRot = TargetRotation;

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
				GetWorld()->GetTimerManager().ClearTimer(ControllerHandle);
			}
		}), 0.016f, true);
}

#pragma endregion