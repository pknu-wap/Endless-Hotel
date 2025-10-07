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

	int32 Grapic;
	FString Language;
	FIntPoint Resolution;
	uint8 Screen;
	float Sound = 0.5f;
};

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API USaveManager : public USaveGame
{
	GENERATED_BODY()

#pragma region Compendium

public:
	TArray<FCompendiumData> LoadCompendiumData();
	void SaveCompendiumData(const FCompendiumData& Data);
	void DeleteCompendiumData();

protected:
	UPROPERTY(SaveGame)
	TArray<FCompendiumData> CompendiumData;

#pragma endregion

#pragma region Setting

public:
	FSettingSaveData LoadSettingData();
	void SaveSettingData(const FSettingSaveData& Data);

protected:
	UPROPERTY(SaveGame)
	FSettingSaveData SettingData;

#pragma endregion

};