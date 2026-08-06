// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Acquire/RoomKey/RoomKey.h"
#include "GameSystem/SaveGame/SaveManager.h"

#pragma region Base

void ARoomKey::BeginPlay()
{
	Super::BeginPlay();

	if (USaveManager::LoadData_Progression().bHasKey)
	{
		Destroy();
	}
}

#pragma endregion

#pragma region Acquire

void ARoomKey::SaveAcquireData()
{
	FSaveData_Progression Data = USaveManager::LoadData_Progression();
	Data.bHasKey = true;
	USaveManager::SaveData_Progression(Data);
}

#pragma endregion