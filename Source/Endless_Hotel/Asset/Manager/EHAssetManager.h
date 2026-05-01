// Copyright by 2026-1 WAP Game 2 team

#pragma once

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
	void LoadAnomalyDataAsset();
	TArray<class UPDA_Anomaly*> GetAnomalyDataAsset(const TArray<uint8>& Indexes);
	bool IsValidIndexAnomalyDataAsset(uint8 Index) { return AnomalyDatas.IsValidIndex(Index); }

private:
	UPROPERTY()
	TArray<TObjectPtr<class UPDA_Anomaly>> AnomalyDatas;

#pragma endregion

};