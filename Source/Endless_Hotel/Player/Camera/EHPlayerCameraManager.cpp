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

void AEHPlayerCameraManager::PossessCamera(const ECameraType& CameraType, const float& BlendTime)
{
	auto* TargetCamera = Cameras.Find(CameraType);

	PC->SetViewTargetWithBlend(TargetCamera->Get(), BlendTime);
}

void AEHPlayerCameraManager::PossessCamera(AActor* CameraOwner, const float& BlendTime)
{
	PC->SetViewTargetWithBlend(CameraOwner, BlendTime);
}

#pragma endregion