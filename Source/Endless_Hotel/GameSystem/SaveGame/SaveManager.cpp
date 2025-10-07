﻿// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/SaveGame/SaveManager.h"
#include "Kismet/GameplayStatics.h"

#pragma region Compendium

TArray<FCompendiumData> USaveManager::LoadCompendiumData()
{
	USaveManager* SaveManager = Cast<USaveManager>(UGameplayStatics::LoadGameFromSlot(TEXT("Save_Compendium"), 0));
	TArray<FCompendiumData> SaveData;

	if (!SaveManager)
	{
		return SaveData;
	}

	SaveData = SaveManager->CompendiumData;

	return SaveData;
}

void USaveManager::SaveCompendiumData(const FCompendiumData& Data)
{
	USaveManager* SaveManager = Cast<USaveManager>(UGameplayStatics::LoadGameFromSlot(TEXT("Save_Compendium"), 0));

	if (!SaveManager)
	{
		SaveManager = Cast<USaveManager>(UGameplayStatics::CreateSaveGameObject(USaveManager::StaticClass()));
	}

	SaveManager->CompendiumData.AddUnique(Data);

	UGameplayStatics::SaveGameToSlot(SaveManager, TEXT("Save_Compendium"), 0);
}

void USaveManager::DeleteCompendiumData()
{
	UGameplayStatics::DeleteGameInSlot(TEXT("Save_Compendium"), 0);
}

#pragma endregion

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