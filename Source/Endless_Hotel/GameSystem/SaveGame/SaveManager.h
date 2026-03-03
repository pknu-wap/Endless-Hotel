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
	static FSaveData_Setting LoadSettingData();
	static void SaveSettingData(const FSaveData_Setting& Data);

protected:
	UPROPERTY(SaveGame)
	FSaveData_Setting Data_Setting;

#pragma endregion

#pragma region Key

public:
	static FSaveData_Key LoadKeyData();
	static void SaveKeyData(const FSaveData_Key& Data);

protected:
	UPROPERTY(SaveGame)
	FSaveData_Key Data_Key;

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