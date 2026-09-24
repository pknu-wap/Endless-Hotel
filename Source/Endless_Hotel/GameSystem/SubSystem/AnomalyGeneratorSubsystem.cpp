// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/SubSystem/AnomalyGeneratorSubsystem.h"

#include "Anomaly/Event/Anomaly_Event.h"
#include "Asset/Manager/EHAssetManager.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "GameSystem/SubSystem/AnomalyPoolSubsystem.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include <Engine/GameInstance.h>
#include <Engine/World.h>

#pragma region AnomalyObject

void UAnomalyGeneratorSubsystem::AnomalyObjectLinker(const TArray<TSubclassOf<AAnomaly_Object_Base>>& TargetClasses) const
{
    if (TargetClasses.IsEmpty())
    {
       return;
    }

    auto* AnomalySub = GetGameInstance()->GetSubsystem<UAnomalyPoolSubsystem>();
    auto ObjectPool = AnomalySub->GetAnomalyObject();

    const EAnomalyID TargetAnomalyName = static_cast<EAnomalyID>(CurrentAnomaly->AnomalyID);

    for (const auto& TargetClass : TargetClasses)
    {
       if (auto* FoundStruct = ObjectPool.Find(TargetClass.Get()))
       {
          for (auto& AnomalyObject : FoundStruct->Objects)
          {
             if (!IsValid(AnomalyObject))
             {
                continue;
             }
             if (AnomalyObject->ExecuteAnomalies.Contains(TargetAnomalyName))
             {
                AnomalyObject->SetAnomalyName(CurrentAnomaly->AnomalyID);
                CurrentAnomaly->LinkedObjects.Add(AnomalyObject);
             }
          }
       }
    }
}

void UAnomalyGeneratorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    Collection.InitializeDependency<UFloorProgressSubsystem>();
    Collection.InitializeDependency<UAnomalyPoolSubsystem>();
    Collection.InitializeDependency<UAnomalyVerdictSubsystem>();

    auto* FloorSub = GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>();
    FloorSub->FloorChange_Reset.AddUObject(this, &ThisClass::SpawnAnomaly);
    bIsInitialFloor = true;
}

#pragma endregion

#pragma region Spawn

void UAnomalyGeneratorSubsystem::SpawnAnomaly()
{
    const auto* FloorSubsystem = GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>();
    auto* VerdictSubsystem = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();
    auto& AssetManager = UEHAssetManager::Get();

    FAnomalySpawnInfo CurrentData = NextAnomalyData.IsSet() ? NextAnomalyData.GetValue() : DecideNext();
    if (FloorSubsystem->Floor == STARTFLOOR && !CurrentData.bIsNormal)
    {
       const FAnomalyEntry& NormalData = AssetManager.GetNormalAnomalyData();
       CurrentData.bIsNormal = true;
       CurrentData.AnomalyID = NormalData.ID;
       CurrentData.DataLayer = NormalData.DataLayer;
       CurrentData.EventClass = NormalData.Event;
       CurrentData.Rule = NormalData.Rule;
    }
    CurrentAnomaly = SpawnFromInfo(CurrentData);

    const TArray<TSubclassOf<AAnomaly_Object_Base>> TargetClasses = AssetManager.GetObjectByID(CurrentAnomaly->AnomalyID);
    AnomalyObjectLinker(TargetClasses);
    VerdictSubsystem->SetCurrentAnomaly(CurrentAnomaly, CurrentAnomaly->AnomalyID, CurrentData.DataLayer);
    NextAnomalyData = DecideNext();
    VerdictSubsystem->SetNextAnomaly(NextAnomalyData->AnomalyID, NextAnomalyData->DataLayer);
    if (bIsInitialFloor)
    {
       bIsInitialFloor = false;
    }
    else
    {
       VerdictSubsystem->OnAnomalySpawned.Broadcast();
    }
}

FAnomalySpawnInfo UAnomalyGeneratorSubsystem::DecideAnomaly(uint8 Index, const bool bForceNormal) const
{
    auto* AnomalySub = GetGameInstance()->GetSubsystem<UAnomalyPoolSubsystem>();
    auto& AssetManager = UEHAssetManager::Get();
    bool bHasAnomaly = AssetManager.IsValidIndexAnomalyData(Index);

    if (!bHasAnomaly)
    {
       AnomalySub->InitializePool();
       Index = AnomalySub->ActIndex;
       bHasAnomaly = AssetManager.IsValidIndexAnomalyData(Index);
    }
    const FAnomalyEntry& Data = bForceNormal || !bHasAnomaly ? AssetManager.GetNormalAnomalyData() : AssetManager.GetActAnomalyByIndex(Index);

    FAnomalySpawnInfo Info;
    Info.bIsNormal = bForceNormal || !bHasAnomaly;
    Info.AnomalyID = Data.ID;
    Info.Rule = Data.Rule;
    Info.DataLayer = Data.DataLayer;
    Info.EventClass = Data.Event;

    return Info;
}

FAnomalySpawnInfo UAnomalyGeneratorSubsystem::DecideNext() const
{
    const auto* AnomalySub = GetGameInstance()->GetSubsystem<UAnomalyPoolSubsystem>();
    constexpr int32 NormalChance = 15;
    const bool bForceNormal = FMath::RandRange(1, 100) <= NormalChance;

    return DecideAnomaly(AnomalySub->ActIndex, bForceNormal);
}

AAnomaly_Event* UAnomalyGeneratorSubsystem::SpawnFromInfo(const FAnomalySpawnInfo& Info) const
{
    UClass* AnomalyClass = Info.EventClass.LoadSynchronous();
    if (!IsValid(AnomalyClass))
    {
       return nullptr;
    }

    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    UWorld* World = GetGameInstance()->GetWorld();
    AAnomaly_Event* Spawned = World->SpawnActor<AAnomaly_Event>(AnomalyClass, FTransform::Identity, Params);

    if (Spawned)
    {
       Spawned->AnomalyID = Info.AnomalyID;
       Spawned->Rule = Info.Rule;
    }
    return Spawned;
}

bool UAnomalyGeneratorSubsystem::SetNextAnomalyForced(const EAnomalyID ID)
{
    const auto& AssetManager = UEHAssetManager::Get();
    auto* VerdictSub = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();

    FAnomalyEntry Data;
    if (!AssetManager.TryGetActAnomalyEntryByID(ID, Data))
    {
       UE_LOG(LogTemp, Warning, TEXT("[AnomalyGeneratorSubsystem] SetNextAnomalyForced failed: ID not in active pool."));
       return false;
    }

    FAnomalySpawnInfo Info;
    Info.bIsNormal = false;
    Info.AnomalyID = Data.ID;
    Info.Rule = Data.Rule;
    Info.DataLayer = Data.DataLayer;
    Info.EventClass = Data.Event;

    NextAnomalyData = Info;
    VerdictSub->SetNextAnomaly(NextAnomalyData->AnomalyID, NextAnomalyData->DataLayer);
    VerdictSub->NextAnomalyID = ID;

    return true;
}

#pragma endregion

#pragma region Reset

void UAnomalyGeneratorSubsystem::ResetGenerator()
{
    CurrentAnomaly = nullptr;
    NextAnomalyData.Reset();
    bIsInitialFloor = true;
}

#pragma endregion