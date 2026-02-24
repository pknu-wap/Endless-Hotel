// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/SaveGame/SaveManager.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include <Kismet/GameplayStatics.h>

#pragma region Setting

FSaveData_Setting USaveManager::LoadSettingData()
{
	USaveManager* SaveManager = Cast<USaveManager>(UGameplayStatics::LoadGameFromSlot(TEXT("Save_Setting"), 0));
	FSaveData_Setting SaveData;

	if (!SaveManager)
	{
		return SaveData;
	}

	SaveData = SaveManager->Data_Setting;

	return SaveData;
}

void USaveManager::SaveSettingData(const FSaveData_Setting& Data)
{
	USaveManager* SaveManager = Cast<USaveManager>(UGameplayStatics::CreateSaveGameObject(USaveManager::StaticClass()));
	SaveManager->Data_Setting = Data;

	UGameplayStatics::SaveGameToSlot(SaveManager, TEXT("Save_Setting"), 0);
}

#pragma endregion

#pragma region Clear

bool USaveManager::LoadGameClearData()
{
	USaveManager* SaveManager = Cast<USaveManager>(UGameplayStatics::LoadGameFromSlot(TEXT("Save_Clear"), 0));
	bool SaveData = false;

	if (!SaveManager)
	{
		return SaveData;
	}

	SaveData = SaveManager->bGameClearData;

	return SaveData;
}

void USaveManager::SaveGameClearData()
{
	USaveManager* SaveManager = Cast<USaveManager>(UGameplayStatics::CreateSaveGameObject(USaveManager::StaticClass()));
	SaveManager->bGameClearData = true;

	UGameplayStatics::SaveGameToSlot(SaveManager, TEXT("Save_Clear"), 0);
}

void USaveManager::DeleteGameClearData()
{
	UGameplayStatics::DeleteGameInSlot(TEXT("Save_Clear"), 0);
}

#pragma endregion

#pragma region Anomaly

TArray<uint8> USaveManager::LoadClearedAnomalyID()
{
	USaveManager* SaveManager = Cast<USaveManager>(UGameplayStatics::LoadGameFromSlot(TEXT("Save_ClearedAnomaly"), 0));
	if (!SaveManager)
	{
		SaveManager = Cast<USaveManager>(UGameplayStatics::CreateSaveGameObject(USaveManager::StaticClass()));
	}
	return SaveManager->ClearedAnomalyID;
}

void USaveManager::SaveClearedAnomalyID(uint8 AnomalyID)
{
	USaveManager* SaveManager = Cast<USaveManager>(UGameplayStatics::LoadGameFromSlot(TEXT("Save_ClearedAnomaly"), 0));
	if (!SaveManager)
	{
		SaveManager = Cast<USaveManager>(UGameplayStatics::CreateSaveGameObject(USaveManager::StaticClass()));
	}
	SaveManager->ClearedAnomalyID.AddUnique(AnomalyID);

	UGameplayStatics::SaveGameToSlot(SaveManager, TEXT("Save_ClearedAnomaly"), 0);
}

#pragma endregion