// Copyright by 2026-1 WAP Game 2 team

#include "GameSystem/SubSystem/AnomalyPoolSubsystem.h"

#include "Asset/Manager/EHAssetManager.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "GameSystem/SubSystem/DataLayerStreamingSubsystem.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include "Anomaly/Event/Anomaly_Event.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include <Engine/GameInstance.h>

#pragma region Base

void UAnomalyPoolSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    Collection.InitializeDependency<UFloorProgressSubsystem>();

    auto& AssetManager = UEHAssetManager::Get();
    AssetManager.InitAnomalyEntries();

    const FSaveData_Setting Data_Setting = USaveManager::LoadData_Setting();
    const FSaveData_Manual Data_Manual = USaveManager::LoadData_Manual();
    bExceptClearedAnomaly = Data_Setting.Overlap == EOptionValue::On;
    AnomalyRules = Data_Manual.ActiveRules;

    bool bIsClear = false;
    if (const UFloorProgressSubsystem* FloorSys = GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>())
    {
        bIsClear = FloorSys->IsGameClear();
    }

    if (bIsClear && bExceptClearedAnomaly)
    {
        const TArray<EAnomalyID> LoadedHistory = USaveManager::LoadClearedAnomalyID();

        AssetManager.ResetClearedAnomaly();
        for (const auto& ID : LoadedHistory)
        {
            AssetManager.MarkAnomalyCleared(ID);
        }
    }

    InitializePool();
}

#pragma endregion

#pragma region Pool

void UAnomalyPoolSubsystem::InitializePool()
{
    auto& AssetManager = UEHAssetManager::Get();
    AnomalyCount = AssetManager.GetOriginAnomaly().Num();
    AssetManager.RebuildActAnomalyFromOrigin();

    ActIndex = 0;

    AssetManager.RemoveNoRuleAnomaly(AnomalyRules);

    if (bExceptClearedAnomaly && !AssetManager.IsClearedAnomalySetEmpty() && AssetManager.GetClearedAnomalyCount() < AnomalyCount)
    {
        AssetManager.RemoveClearedAnomaly();
    }

    AssetManager.ShuffleActAnomaly();

    // Reset Index
    ActIndex = 0;
}

void UAnomalyPoolSubsystem::RegisterAnomalyObject(AAnomaly_Object_Base* Object)
{
    if (!IsValid(Object))
    {
        return;
    }

    UClass* ActorClass = Object->GetClass();
    AnomalyObjectPool.FindOrAdd(ActorClass).Objects.AddUnique(Object);

    UFloorProgressSubsystem* FloorSys = GetGameInstance() ? GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>() : nullptr;
    if (FloorSys)
    {
        FloorSys->FloorChange_Reset.AddUniqueDynamic(Object, &AAnomaly_Object_Base::Reset);
    }

    const UDataLayerStreamingSubsystem* DataLayerSys = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDataLayerStreamingSubsystem>() : nullptr;
    if (DataLayerSys && DataLayerSys->IsDataLayerVisited(DataLayerSys->GetCurrentDataLayer()))
    {
        Object->Reset();
    }
}

void UAnomalyPoolSubsystem::UnRegisterAnomalyObject(AAnomaly_Object_Base* Object)
{
    if (!Object)
    {
        return;
    }

    UClass* TargetClass = Object->GetClass();
    if (FAnomalyObjectArray* FoundStruct = AnomalyObjectPool.Find(TargetClass))
    {
        FoundStruct->Objects.Remove(Object);
        if (FoundStruct->Objects.IsEmpty())
        {
            AnomalyObjectPool.Remove(TargetClass);
        }

        UAnomalyVerdictSubsystem* VerdictSys = GetGameInstance() ? GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>() : nullptr;
        if (VerdictSys && IsValid(VerdictSys->GetCurrentAnomaly()))
        {
            VerdictSys->GetCurrentAnomaly()->LinkedObjects.Remove(Object);
        }
    }
}

#pragma endregion

#pragma region ManualRule

void UAnomalyPoolSubsystem::AddAnomalyRule(const EAnomalyRule& AnomalyRule)
{
    AnomalyRules.AddUnique(AnomalyRule);

    FSaveData_Manual SavedRules;
    SavedRules.ActiveRules = AnomalyRules;
    USaveManager::SaveData_Manual(SavedRules);

    InitializePool();
    OnAddAnomalyRule.Broadcast(AnomalyRule);
}

void UAnomalyPoolSubsystem::RemoveAnomalyRule(const EAnomalyRule& AnomalyRule)
{
    AnomalyRules.Remove(AnomalyRule);

    FakeManualEntries.RemoveAll([AnomalyRule](const FFakeManualEntry& Entry)
        {
            return Entry.RealRuleToSolve == AnomalyRule;
        });

    FSaveData_Manual SavedRules;
    SavedRules.ActiveRules = AnomalyRules;
    USaveManager::SaveData_Manual(SavedRules);

    InitializePool();
    OnAddAnomalyRule.Broadcast(AnomalyRule);
}

void UAnomalyPoolSubsystem::AddFakeManualEntry(EAnomalyID TargetAnomalyID, EAnomalyRule FakeAction, EAnomalyRule RealRule)
{
    FFakeManualEntry NewEntry;
    NewEntry.TargetAnomalyID = TargetAnomalyID;
    NewEntry.DisplayedFakeAction = FakeAction;
    NewEntry.RealRuleToSolve = RealRule;

    FakeManualEntries.Add(NewEntry);
    OnAddAnomalyRule.Broadcast(FakeAction);
}

void UAnomalyPoolSubsystem::ClearFakeManualEntry(EAnomalyID TargetAnomalyID)
{
    FakeManualEntries.RemoveAll([TargetAnomalyID](const FFakeManualEntry& Entry)
        {
            return Entry.TargetAnomalyID == TargetAnomalyID;
        });
}

#pragma endregion

#pragma region Reset

void UAnomalyPoolSubsystem::ResetPool()
{
    AnomalyCount = 0;
    ActIndex = 0;
    AnomalyObjectPool.Empty();

    bExceptClearedAnomaly = USaveManager::LoadData_Setting().Overlap == EOptionValue::On;

    InitializePool();
}

#pragma endregion