// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveManager.generated.h"

#pragma region Declare

USTRUCT(BlueprintType)
struct FRecordingData
{
	GENERATED_BODY()

	int32 Index;
	bool bIsChecked;

	bool operator==(const FRecordingData& Data) const
	{
		return Index == Data.Index && bIsChecked == Data.bIsChecked;
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

#pragma region Recording

public:
	TArray<FRecordingData> LoadRecordingData();
	void SaveRecordingData(const FRecordingData& Data);
	void DeleteRecordingData();

protected:
	UPROPERTY(SaveGame)
	TArray<FRecordingData> RecordingData;

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