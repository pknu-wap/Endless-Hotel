// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Camera/EHCameraActor.h"
#include "Player/Camera/EHPlayerCameraManager.h"
#include <Kismet/GameplayStatics.h>

#pragma region Base

void AEHCameraActor::BeginPlay()
{
	Super::BeginPlay();

	RegisterCamera();
}

#pragma endregion

#pragma region Register

void AEHCameraActor::RegisterCamera()
{
	auto* CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	CameraManager->RegisterCamera(CameraType, this);
}

#pragma endregion