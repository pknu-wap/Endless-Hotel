// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Type/Anomaly/Type_AnomalyID.h"
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


USTRUCT(BlueprintType)
struct FFakeManualEntry
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    EAnomalyID TargetAnomalyID = EAnomalyID::None;

    UPROPERTY(EditAnywhere)
    EAnomalyRule DisplayedFakeAction = EAnomalyRule::None;

    UPROPERTY(EditAnywhere)
    EAnomalyRule RealRuleToSolve = EAnomalyRule::None;
};

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API UAnomalyPoolSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

#pragma region Base

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

#pragma endregion

#pragma region Pool

public:
    void InitializePool();
    void RegisterAnomalyObject(AAnomaly_Object_Base* Object);
    void UnRegisterAnomalyObject(AAnomaly_Object_Base* Object);
    TMap<TObjectPtr<UClass>, FAnomalyObjectArray> GetAnomalyObject() { return AnomalyObjectPool; }

public:
    uint8 AnomalyCount = 0;
    uint8 ActIndex = 0;
    bool bExceptClearedAnomaly = false;

private:
    UPROPERTY()
    TMap<TObjectPtr<UClass>, FAnomalyObjectArray> AnomalyObjectPool;

#pragma endregion

#pragma region ManualRule

public:
    void AddAnomalyRule(const EAnomalyRule& AnomalyRule);
    void RemoveAnomalyRule(const EAnomalyRule& AnomalyRule);
    void AddFakeManualEntry(EAnomalyID TargetAnomalyID, EAnomalyRule FakeAction, EAnomalyRule RealRule);
    void ClearFakeManualEntry(EAnomalyID TargetAnomalyID);

public:
    TArray<EAnomalyRule> AnomalyRules = { EAnomalyRule::EightExit, EAnomalyRule::Touch, EAnomalyRule::Watch,
        EAnomalyRule::Doll, EAnomalyRule::Painting, EAnomalyRule::ResetObject, EAnomalyRule::TurnOffSound };

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddAnomalyRule, EAnomalyRule, Rule);
    FOnAddAnomalyRule OnAddAnomalyRule;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddFakeManualEntry, const FFakeManualEntry&, Entry);
    FOnAddFakeManualEntry OnAddFakeManualEntry;

private:
    UPROPERTY()
    TArray<FFakeManualEntry> FakeManualEntries;

#pragma endregion

#pragma region Reset

public:
    void ResetPool();

#pragma endregion

};