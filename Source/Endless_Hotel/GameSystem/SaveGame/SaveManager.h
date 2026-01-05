// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/Save/Type_Save.h"
#include <CoreMinimal.h>
#include <GameFramework/SaveGame.h>
#include <SaveManager.generated.h>

UCLASS()
class ENDLESS_HOTEL_API USaveManager : public USaveGame
{
	GENERATED_BODY()

#pragma region Setting

public:
	static FSettingSaveData LoadSettingData();
	static void SaveSettingData(const FSettingSaveData& Data);

protected:
	UPROPERTY(SaveGame)
	FSettingSaveData SettingData;

#pragma endregion

#pragma region Clear

public:
	static bool LoadGameClearData();
	static void SaveGameClearData();
	static void DeleteGameClearData();

protected:
	UPROPERTY(SaveGame)
	bool bGameClearData = false;

#pragma endregion

#pragma region Anomaly

public:
	static TArray<uint8> LoadClearedAnomalyID();
	static void SaveClearedAnomalyID(uint8 AnomalyID);

protected:
	UPROPERTY(SaveGame)
	TArray<uint8> ClearedAnomalyID;

#pragma endregion

};