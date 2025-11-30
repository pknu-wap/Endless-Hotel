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

	int32 Index;
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

	int32				Value_Grapic;
	FString				Value_Language;
	FIntPoint			Value_Resolution;
	EWindowMode::Type	Value_Screen;
	float				Value_Frame;
	float				Value_Sound = 0.5f;
	float				Value_Brightness = 0;

	int32 Index_Grapic;
	int32 Index_Language;
	int32 Index_Resolution;
	int32 Index_Screen;
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