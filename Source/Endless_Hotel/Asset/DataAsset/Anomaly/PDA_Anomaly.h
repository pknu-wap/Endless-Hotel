// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Type/Anomaly/Type_AnomalyID.h"
#include "Type/Level/Type_Level.h"
#include "Type/Anomaly/Type_AnomalyEntry.h"
#include <CoreMinimal.h>
#include <Engine/DataAsset.h>
#include <PDA_Anomaly.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UPDA_Anomaly : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("Anomaly", GetFName()); }

public:
	UPROPERTY(EditAnywhere, Category = "Anomaly")
	TArray<FAnomalyEntry> Entries;
};