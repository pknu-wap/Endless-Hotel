// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Type/Anomaly/Type_AnomalyEntry.h"
#include <CoreMinimal.h>
#include <Engine/AssetManager.h>
#include <EHAssetManager.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UEHAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
#pragma region Base

public:
	static UEHAssetManager& Get() { return *Cast<UEHAssetManager>(GEngine->AssetManager); }

#pragma endregion

#pragma region Anomaly

public:
	FAnomalyEntry GetAnomalyData(uint8 Index);
	TArray<FAnomalyEntry> GetAnomalyData(TArray<uint8> Indexes);
	TArray<FAnomalyEntry> GetAnomalyData(TArray<EAnomalyID> IDs);

	bool IsValidIndexAnomalyData(uint8 Index) { return Data_Anomalies.IsValidIndex(Index); }

private:
	void LoadAnomalyData();

private:
	UPROPERTY()
	TArray<FAnomalyEntry> Data_Anomalies;

#pragma endregion

};