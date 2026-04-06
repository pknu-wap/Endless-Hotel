// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/SaveGame/SaveManager.h"

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