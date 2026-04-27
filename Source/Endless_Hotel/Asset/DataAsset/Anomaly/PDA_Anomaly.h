// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Type/Anomaly/Type_AnomalyID.h"
#include <CoreMinimal.h>
#include <Engine/DataAsset.h>
#include <PDA_Anomaly.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UPDA_Anomaly : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId(TEXT("Anomaly"), GetFName()); }

public:
	UPROPERTY(EditAnywhere, Category = "InGame|Data")
	uint8 Number = 0;

	UPROPERTY(EditAnywhere, Category = "InGame|Data")
	EAnomalyID ID = EAnomalyID::None;

	UPROPERTY(EditAnywhere, Category = "InGame|Data", meta = (AssetBundles = "InGame"))
	TSoftClassPtr<class AAnomaly_Event> Anomaly;

	UPROPERTY(EditAnywhere, Category = "InGame|Data", meta = (AssetBundles = "InGame"))
	TArray<TSoftClassPtr<class AAnomaly_Event>> Objects;

public:
	UPROPERTY(EditAnywhere, Category = "UI|Description", meta = (AssetBundles = "UI"))
	TSoftObjectPtr<class UTexture2D> Image_Description;

	UPROPERTY(EditAnywhere, Category = "UI|Description")
	FText Text_Description;
};