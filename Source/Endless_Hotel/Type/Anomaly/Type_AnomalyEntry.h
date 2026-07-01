// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Type/Anomaly/Type_AnomalyID.h"
#include "Type/Level/Type_Level.h"
#include <CoreMinimal.h>
#include <Type_AnomalyEntry.generated.h>

USTRUCT(BlueprintType)
struct FAnomalyEntry
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "InGame|Data")
    EAnomalyID ID = EAnomalyID::None;

    UPROPERTY(EditAnywhere, Category = "InGame|Data", meta = (AssetBundles = "InGame"))
    TSoftClassPtr<class AAnomaly_Event> Event;

    UPROPERTY(EditAnywhere, Category = "InGame|Data", meta = (AssetBundles = "InGame"))
    TArray<TSoftClassPtr<class AAnomaly_Object_Base>> Objects;

    UPROPERTY(EditAnywhere, Category = "InGame|Data")
    EMapDataLayer DataLayer = EMapDataLayer::Hotel;

    UPROPERTY(EditAnywhere, Category = "UI|Description", meta = (AssetBundles = "UI"))
    TSoftObjectPtr<class UTexture2D> Image_Description;

    UPROPERTY(EditAnywhere, Category = "UI|Description")
    FText Text_Description;
};