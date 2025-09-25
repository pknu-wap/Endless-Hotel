// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/SaveGame/SaveManager.h"
#include "Kismet/GameplayStatics.h"

#pragma region Setting

FSettingSaveData USaveManager::LoadSettingData()
{
	USaveManager* SaveManager = Cast<USaveManager>(UGameplayStatics::LoadGameFromSlot(TEXT("Save_Setting"), 0));
	FSettingSaveData SaveData;

	if (!SaveManager)
	{
		return SaveData;
	}

	SaveData = SaveManager->SettingData;

	return SaveData;
}

void USaveManager::SaveSettingData(const FSettingSaveData& Data)
{
	USaveManager* SaveManager = Cast<USaveManager>(UGameplayStatics::CreateSaveGameObject(USaveManager::StaticClass()));
	SaveManager->SettingData = Data;

	UGameplayStatics::SaveGameToSlot(SaveManager, TEXT("Save_Setting"), 0);
}

#pragma endregion