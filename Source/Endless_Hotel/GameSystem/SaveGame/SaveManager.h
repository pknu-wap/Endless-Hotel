// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveManager.generated.h"

#pragma region Declare

USTRUCT(BlueprintType)
struct FCompendiumData
{
	GENERATED_BODY()

	UPROPERTY(SaveGame)
	int32 Index;

	UPROPERTY(SaveGame)
	bool bIsChecked;

	bool operator==(const FCompendiumData& Data) const
	{
		return Index == Data.Index;
	}
};

USTRUCT(BlueprintType)
struct FSettingSaveData
{
	GENERATED_BODY()

	UPROPERTY(SaveGame)
	int32 Value_Grapic;

	UPROPERTY(SaveGame)
	FString Value_Language;

	UPROPERTY(SaveGame)
	FIntPoint Value_Resolution;

	UPROPERTY(SaveGame)
	uint8 Value_Screen;

	UPROPERTY(SaveGame)
	float Value_Frame;

	UPROPERTY(SaveGame)
	float Value_Sound = 0.5f;

	UPROPERTY(SaveGame)
	float Value_Brightness = 0;

	UPROPERTY(SaveGame)
	int32 Index_Grapic;

	UPROPERTY(SaveGame)
	int32 Index_Language;

	UPROPERTY(SaveGame)
	int32 Index_Resolution;

	UPROPERTY(SaveGame)
	int32 Index_Screen;

	UPROPERTY(SaveGame)
	int32 Index_Frame;
};

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API USaveManager : public USaveGame
{
	GENERATED_BODY()

#pragma region Compendium

public:
	static TArray<FCompendiumData> LoadCompendiumData();
	static void SaveCompendiumData(const FCompendiumData& Data);
	static void DeleteCompendiumData();

protected:
	UPROPERTY(SaveGame)
	TArray<FCompendiumData> CompendiumData;

#pragma endregion

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

};