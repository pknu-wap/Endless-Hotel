// Copyright by 2026-1 WAP Game 2 team

#include "Player/Camera/EHPlayerCameraManager.h"
#include "Player/Controller/EHPlayerController.h"
#include "Actor/Camera/EHCameraActor.h"

#pragma region Base

void AEHPlayerCameraManager::BeginPlay()
{
	Super::BeginPlay();

	SetReference();
}

#pragma endregion

#pragma region Reference

void AEHPlayerCameraManager::SetReference()
{
	PC = Cast<AEHPlayerController>(GetOwningPlayerController());
}

#pragma endregion

#pragma region Possess

void AEHPlayerCameraManager::PossessCamera(const FName& CameraTag, const float& BlendTime)
{
	auto* TargetCamera = Cameras.Find(CameraTag);
	
	PC->SetViewTargetWithBlend(TargetCamera->Get(), BlendTime);
}

#pragma endregion