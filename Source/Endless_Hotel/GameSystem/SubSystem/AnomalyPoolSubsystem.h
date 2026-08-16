// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Type/Anomaly/Type_AnomalyRule.h"
#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <AnomalyPoolSubsystem.generated.h>

#pragma region Declare

class AAnomaly_Object_Base;

USTRUCT(BlueprintType)
struct FAnomalyObjectArray
{
    GENERATED_BODY()

public:
    UPROPERTY()
    TArray<TObjectPtr<AAnomaly_Object_Base>> Objects;
};

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API UAnomalyPoolSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    void InitializePool();
    void RegisterAnomalyObject(AAnomaly_Object_Base* Object);
    void UnRegisterAnomalyObject(AAnomaly_Object_Base* Object);
    void AddAnomalyRule(const EAnomalyRule& AnomalyRule);
    void RemoveAnomalyRule(const EAnomalyRule& AnomalyRule);
    TMap<TObjectPtr<UClass>, FAnomalyObjectArray> GetAnomalyObject() { return AnomalyObjectPool; }

    void ResetPool();

public:
    uint8 AnomalyCount = 0;
    uint8 ActIndex = 0;
    bool bExceptClearedAnomaly = false;
    TArray<EAnomalyRule> AnomalyRules = { EAnomalyRule::EightExit, EAnomalyRule::Touch, EAnomalyRule::Watch,
        EAnomalyRule::Doll, EAnomalyRule::Painting, EAnomalyRule::ResetObject, EAnomalyRule::TurnOffSound };

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddAnomalyRule, EAnomalyRule, Rule);
    FOnAddAnomalyRule OnAddAnomalyRule;

private:
    UPROPERTY()
    TMap<TObjectPtr<UClass>, FAnomalyObjectArray> AnomalyObjectPool;
};