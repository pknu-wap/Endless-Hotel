// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Type/UI/Type_Setting.h"
#include <CoreMinimal.h>
#include <Engine/DataAsset.h>
#include <PDA_Option.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UPDA_Option : public UPrimaryDataAsset
{
	GENERATED_BODY()

#pragma region Data

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("Option", GetFName()); }

#pragma endregion

#pragma region Option

public:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSoftClassPtr<class UUI_Base> Class;

	UPROPERTY(EditDefaultsOnly, Category = "Option")
	EOptionCategory Category = EOptionCategory::None;

	UPROPERTY(EditDefaultsOnly, Category = "Option")
	TArray<EOptionValue> Values;

#pragma endregion

};