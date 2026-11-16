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

void UBedDirectionComponent::ShowEyeEffect(bool bOpen)
{
	CameraManager->StartEyeEffect(bOpen);

	auto* UICon = GetWorld()->GetGameInstance()->GetSubsystem<UUI_Controller>();
	auto* UI_InGame = Cast<UUI_HUD_InGame>(UICon->GetHUDWidget());
	UI_InGame->StartInGameHUD(bOpen);
}

void UBedDirectionComponent::ShowEyeFastEffect()
{
	CameraManager->StartFastEyeEffect();

	auto* UICon = GetWorld()->GetGameInstance()->GetSubsystem<UUI_Controller>();
	auto* UI_InGame = Cast<UUI_HUD_InGame>(UICon->GetHUDWidget());
	UI_InGame->RemoveEyeEffectBlur();
}

void UBedDirectionComponent::SyncCameraRotation(bool bOn)
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	if (!bOn)
	{
		TimerManager.ClearTimer(ControllerHandle);
		return;
	}

	TimerManager.SetTimer(ControllerHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			PC->SetControlRotation(Player->GetActorRotation());
		}), 0.01f, true);
}

#pragma endregion