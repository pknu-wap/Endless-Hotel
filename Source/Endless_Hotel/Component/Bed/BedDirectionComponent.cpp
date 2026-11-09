// Copyright by 2026-1 WAP Game 2 team

#include "Component/Bed/BedDirectionComponent.h"
#include "Player/Character/EHPlayer.h"
#include "Player/Controller/EHPlayerController.h"
#include "Player/Camera/EHPlayerCameraManager.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/HUD/InGame/UI_HUD_InGame.h"
#include <Kismet/GameplayStatics.h>
#include <Components/CapsuleComponent.h>
#include <Kismet/KismetSystemLibrary.h>

#pragma region Base

void UBedDirectionComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerRoot = Cast<UCapsuleComponent>(Player->GetRootComponent());
	PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
}

#pragma endregion

#pragma region Direction

void UBedDirectionComponent::SetPlayerInputAble(bool bAble)
{
	PC->SetPlayerInputAble(bAble);
	PlayerRoot->SetEnableGravity(bAble);

	ECollisionEnabled::Type CE = bAble ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision;
	PlayerRoot->SetCollisionEnabled(CE);
}

void UBedDirectionComponent::ShowDirection(TArray<FBedDirectionInfo> Infos)
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

void UBedDirectionComponent::ShowEyeEffect(bool bOpen)
{
	CameraManager->StartEyeEffect(bOpen);

	auto* UICon = GetWorld()->GetGameInstance()->GetSubsystem<UUI_Controller>();
	auto* UI_InGame = Cast<UUI_HUD_InGame>(UICon->GetHUDWidget());
	UI_InGame->StartInGameHUD(bOpen);
}

void UBedDirectionComponent::AdjustControllerRotation(const FRotator& TargetRotation, float Duration)
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