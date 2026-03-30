// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/Save/Type_Save.h"
#include <CoreMinimal.h>
#include <GameFramework/SaveGame.h>
#include <Kismet/GameplayStatics.h>
#include <SaveManager.generated.h>

#pragma region Macro

#define DATA_SAVE_DEFINITION(ReturnType, TargetData) \
static ReturnType Load##TargetData() \
{ \
	FString SlotName = TEXT(#TargetData); \
	USaveManager* SaveManager = Cast<USaveManager>(UGameplayStatics::LoadGameFromSlot(SlotName, 0)); \
	ReturnType SaveData{}; \
	if (!SaveManager) \
	{ \
		return SaveData; \
	} \
	SaveData = SaveManager->TargetData; \
	return SaveData; \
} \
static void Save##TargetData(const ReturnType& Data) \
{ \
	FString SlotName = TEXT(#TargetData); \
	USaveManager* SaveManager = Cast<USaveManager>(UGameplayStatics::LoadGameFromSlot(SlotName, 0)); \
    if (!SaveManager) \
    { \
        SaveManager = Cast<USaveManager>(UGameplayStatics::CreateSaveGameObject(USaveManager::StaticClass())); \
    } \
	SaveManager->TargetData = Data; \
	UGameplayStatics::SaveGameToSlot(SaveManager, SlotName, 0); \
} \
static void Delete##TargetData() \
{ \
	FString SlotName = TEXT(#TargetData); \
	UGameplayStatics::DeleteGameInSlot(SlotName, 0); \
}

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API USaveManager : public USaveGame
{
	GENERATED_BODY()

#pragma region Setting

public:
	DATA_SAVE_DEFINITION(FSaveData_Setting, Data_Setting);

protected:
	UPROPERTY(SaveGame)
	FSaveData_Setting Data_Setting;

#pragma endregion

#pragma region Key

public:
	DATA_SAVE_DEFINITION(FSaveData_Key, Data_Key);

protected:
	UPROPERTY(SaveGame)
	FSaveData_Key Data_Key;

#pragma endregion

#pragma region Clear

public:
	DATA_SAVE_DEFINITION(bool, Data_GameClear);

protected:
	UPROPERTY(SaveGame)
	bool Data_GameClear = false;

#pragma endregion

#pragma region Anomaly

public:
	static TArray<uint8> LoadClearedAnomalyID();
	static void SaveClearedAnomalyID(uint8 AnomalyID);

protected:
	UPROPERTY(SaveGame)
	TArray<uint8> ClearedAnomalyID;

#pragma endregion

#pragma region Tutorial

public:
	DATA_SAVE_DEFINITION(FSaveData_Tutorial, Data_Tutorial);

protected:
	UPROPERTY(SaveGame)
	FSaveData_Tutorial Data_Tutorial;

#pragma endregion

#pragma region Manual

public:
	DATA_SAVE_DEFINITION(FSaveData_Manual, Data_Manual);

protected:
	UPROPERTY(SaveGame)
	FSaveData_Manual Data_Manual;

#pragma endregion

};