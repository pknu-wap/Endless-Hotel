// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Engine/DataAsset.h>
#include <PDA_Map.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UPDA_Map : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId(TEXT("Anomaly"), GetFName()); }

public:
	UPROPERTY(EditAnywhere, Category = "Level", meta = (AssetBundles = "Level"))
	TSoftObjectPtr<UWorld> Level_MainMenu;

	UPROPERTY(EditAnywhere, Category = "Level", meta = (AssetBundles = "Level"))
	TSoftObjectPtr<UWorld> Level_Hotel;

	UPROPERTY(EditAnywhere, Category = "Level", meta = (AssetBundles = "Level"))
	TSoftObjectPtr<UWorld> Level_Loading;

public:
	UPROPERTY(EditAnywhere, Category = "DataLayer", meta = (AssetBundles = "DataLayer"))
	TSoftObjectPtr<UDataLayerAsset> DL_Default;

	UPROPERTY(EditAnywhere, Category = "DataLayer", meta = (AssetBundles = "DataLayer"))
	TSoftObjectPtr<UDataLayerAsset> DL_Hotel;

	UPROPERTY(EditAnywhere, Category = "DataLayer", meta = (AssetBundles = "DataLayer"))
	TSoftObjectPtr<UDataLayerAsset> DL_Fire;

	UPROPERTY(EditAnywhere, Category = "DataLayer", meta = (AssetBundles = "DataLayer"))
	TSoftObjectPtr<UDataLayerAsset> DL_Maze;

	UPROPERTY(EditAnywhere, Category = "DataLayer", meta = (AssetBundles = "DataLayer"))
	TSoftObjectPtr<UDataLayerAsset> DL_Choice;
};