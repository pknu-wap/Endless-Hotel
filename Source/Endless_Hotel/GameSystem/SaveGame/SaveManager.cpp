// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/SaveGame/SaveManager.h"
#include "Kismet/GameplayStatics.h"

#pragma region Recording

TArray<FRecordingData> USaveManager::LoadRecordingData()
{
	USaveManager* SaveManager = Cast<USaveManager>(UGameplayStatics::LoadGameFromSlot(TEXT("Save_Recording"), 0));
	TArray<FRecordingData> SaveData;

	if (!SaveManager)
	{
		return SaveData;
	}

	SaveData = SaveManager->RecordingData;

	return SaveData;
}

void USaveManager::SaveRecordingData(const FRecordingData& Data)
{
	USaveManager* SaveManager = Cast<USaveManager>(UGameplayStatics::LoadGameFromSlot(TEXT("Save_Recording"), 0));

	if (!SaveManager)
	{
		SaveManager = Cast<USaveManager>(UGameplayStatics::CreateSaveGameObject(USaveManager::StaticClass()));
	}

	SaveManager->RecordingData.AddUnique(Data);

	UGameplayStatics::SaveGameToSlot(SaveManager, TEXT("Save_Recording"), 0);
}

void USaveManager::DeleteRecordingData()
{
	UGameplayStatics::DeleteGameInSlot(TEXT("Save_Recording"), 0);
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