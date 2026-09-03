// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Acquire/Lighter/Lighter.h"
#include "GameSystem/SaveGame/SaveManager.h"

#pragma region Base

void ALighter::BeginPlay()
{
	Super::BeginPlay();

	if (USaveManager::LoadData_Progression().bHasFlash)
	{
		Destroy();
	}
}

#pragma endregion

#pragma region Acquire

void ALighter::SaveAcquireData()
{
	FSaveData_Progression Data = USaveManager::LoadData_Progression();
	Data.bHasFlash = true;
	USaveManager::SaveData_Progression(Data);
}

#pragma endregion