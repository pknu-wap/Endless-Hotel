// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Engine/DataAsset.h>
#include <PDA_Level.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UPDA_Level : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("Level", GetFName()); }

public:
	UPROPERTY(EditAnywhere, Category = "DataLayer", meta = (AssetBundles = "DataLayer"))
	TSoftObjectPtr<UDataLayerAsset> DL_Default;

	UPROPERTY(EditAnywhere, Category = "DataLayer", meta = (AssetBundles = "DataLayer"))
	TSoftObjectPtr<UDataLayerAsset> DL_Lobby;

	UPROPERTY(EditAnywhere, Category = "DataLayer", meta = (AssetBundles = "DataLayer"))
	TSoftObjectPtr<UDataLayerAsset> DL_Hotel;

	UPROPERTY(EditAnywhere, Category = "DataLayer", meta = (AssetBundles = "DataLayer"))
	TSoftObjectPtr<UDataLayerAsset> DL_Fire;

	UPROPERTY(EditAnywhere, Category = "DataLayer", meta = (AssetBundles = "DataLayer"))
	TSoftObjectPtr<UDataLayerAsset> DL_Maze;

	UPROPERTY(EditAnywhere, Category = "DataLayer", meta = (AssetBundles = "DataLayer"))
	TSoftObjectPtr<UDataLayerAsset> DL_Choice;
};