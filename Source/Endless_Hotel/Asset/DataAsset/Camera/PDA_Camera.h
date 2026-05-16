// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Engine/DataAsset.h>
#include <PDA_Camera.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UPDA_Camera : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("Camera", GetFName()); }

public:
	UPROPERTY(EditAnywhere, Category = "EyeEffect", meta = (AssetBundles = "EyeEffect"))
	TSoftObjectPtr<UMaterial> M_EyeEffect;

	UPROPERTY(EditAnywhere, Category = "EyeEffect", meta = (AssetBundles = "EyeEffect"))
	TSoftObjectPtr<UCurveFloat> CV_EyeOpen;
};