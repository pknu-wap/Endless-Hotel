// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Bed/Bed_Ending.h"
#include "Player/Character/EHPlayer.h"
#include "Player/Controller/EHPlayerController.h"
#include "Player/Camera/EHPlayerCameraManager.h"
#include "UI/Controller/UI_Controller.h"
#include <Kismet/GameplayStatics.h>

#pragma region Interact

void ABed_Ending::Interact(AEHCharacter* Interacter)
{
	Super::Interact(Interacter);

	FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();
	switch (Info.InteractType)
	{
	case EInteractType::Sleep:
		MoveToBedForSleep();
		break;
	}
}

#pragma endregion

#pragma region Sleep

void ABed_Ending::MoveToBedForSleep()
{
	PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->SetPlayerInputAble(false);

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = TEXT("SleepBadEnding");
	LatentInfo.UUID = __LINE__;
	LatentInfo.Linkage = 0;

	auto* EHPlayer = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	constexpr float Duration = 1.0f;
	UKismetSystemLibrary::MoveComponentTo(EHPlayer->GetRootComponent(), Trans_Sleep.GetLocation(), Trans_Sleep.Rotator(), false, false, Duration, false, EMoveComponentAction::Move, LatentInfo);
	StartControllerRotation(Trans_Sleep.Rotator(), Duration);
}

void ABed_Ending::SleepBadEnding()
{
	auto* CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	CameraManager->StartEyeEffect(false);

	FTimerHandle DelayHandle;
	GetWorld()->GetTimerManager().SetTimer(DelayHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
			UICon->OpenWidget(EWidgetType::PopUp_Credit_Bad);
		}), 6.f, false);
}

void ABed_Ending::StartControllerRotation(const FRotator& TargetRotation, float Duration)
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
				World->GetTimerManager().ClearTimer(ControllerHandle);
			}
		}), 0.016f, true);
}

#pragma endregion