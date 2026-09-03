// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Type/UI/Type_Setting.h"
#include <CoreMinimal.h>
#include <Engine/DataAsset.h>
#include <PDA_Setting.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UPDA_Setting : public UPrimaryDataAsset
{
	GENERATED_BODY()

#pragma region Data

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("Setting", GetFName()); }

#pragma endregion

#pragma region Setting

public:
	UPROPERTY(EditDefaultsOnly, Category = "Setting")
	TMap<ESettingCategory, FOptionList> Setting;

#pragma endregion

};