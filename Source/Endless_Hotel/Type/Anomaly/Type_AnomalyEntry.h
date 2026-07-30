// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Type/Anomaly/Type_AnomalyID.h"
#include "Type/Anomaly/Type_AnomalyRule.h"
#include "Type/Level/Type_Level.h"
#include <CoreMinimal.h>
#include <Type_AnomalyEntry.generated.h>

USTRUCT(BlueprintType)
struct FAnomalyEntry
{
    GENERATED_BODY()

public:
    FAnomalyEntry() = default;
	FAnomalyEntry(EAnomalyID New) :ID(New) {}
    FAnomalyEntry(uint8 Index)
    {
        ID = static_cast<EAnomalyID>(Index);
    }

public:
    UPROPERTY(EditAnywhere, Category = "InGame|Data")
    EAnomalyID ID = EAnomalyID::None;

    UPROPERTY(EditAnywhere, Category = "InGame|Data")
    EAnomalyRule Rule = EAnomalyRule::EightExit;

    UPROPERTY(EditAnywhere, Category = "InGame|Data")
    EMapDataLayer DataLayer = EMapDataLayer::Hotel;

    UPROPERTY(EditAnywhere, Category = "InGame|Class")
    TSoftClassPtr<class AAnomaly_Event> Event;

    UPROPERTY(EditAnywhere, Category = "InGame|Class")
    TArray<TSoftClassPtr<class AAnomaly_Object_Base>> Objects;

    UPROPERTY(EditAnywhere, Category = "UI|Description")
    TSoftObjectPtr<class UTexture2D> Picture;

    UPROPERTY(EditAnywhere, Category = "UI|Description")
    FText Description;
};

FORCEINLINE bool operator==(const FAnomalyEntry& First, const FAnomalyEntry& Second)
{
    return First.ID == Second.ID;
}

FORCEINLINE uint32 GetTypeHash(const FAnomalyEntry& Entry)
{
    return GetTypeHash(Entry.ID);
}