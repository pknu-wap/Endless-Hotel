// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Interact/Acquire/Lighter/Lighter.h"
#include "GameSystem/SaveGame/SaveManager.h"

#pragma region Base

void ALighter::BeginPlay()
{
	Super::BeginPlay();

	if (USaveManager::LoadData_Tutorial().bHasFlash)
	{
		Destroy();
	}
}

#pragma endregion

#pragma region Acquire

void ALighter::SaveAcquireData()
{
	FSaveData_Tutorial Data = USaveManager::LoadData_Tutorial();
	Data.bHasFlash = true;
	USaveManager::SaveData_Tutorial(Data);
}

#pragma endregion