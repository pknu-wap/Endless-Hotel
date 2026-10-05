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
   auto* VerdictSubsystem = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();
   TOptional<FAnomalySpawnInfo> CurrentData = NextAnomalyData.IsSet() ? NextAnomalyData : DecideNext();
   auto& AssetManager = UEHAssetManager::Get();

   if (!CurrentData.IsSet() || CurrentData->bIsNormal)
   {
      ApplyNormalFloor();
      NotifySpawned();
      return;
   }
   
   const FAnomalySpawnInfo& SpawnInfo = CurrentData.GetValue();
   CurrentAnomaly = SpawnFromInfo(CurrentData.GetValue());
   if (!CurrentAnomaly)
   {
      ApplyNormalFloor();
      return;
   }
   AnomalyObjectLinker(AssetManager.GetObjectByID(CurrentAnomaly->AnomalyID));
   VerdictSubsystem->SetCurrentAnomaly(CurrentAnomaly, CurrentAnomaly->AnomalyID, SpawnInfo.DataLayer);
   
   NextAnomalyData = DecideNext();
   if (NextAnomalyData.IsSet())
   {
      VerdictSubsystem->SetNextAnomaly(NextAnomalyData->AnomalyID, NextAnomalyData->DataLayer);
   }
   else
   {
      VerdictSubsystem->SetNextAnomaly(EAnomalyID::Normal, EMapDataLayer::Hotel);
   }
   NotifySpawned();
}

void UAnomalyGeneratorSubsystem::ForceNormalNext()
{
   FAnomalySpawnInfo Info;
   Info.bIsNormal = true;
   Info.AnomalyID = EAnomalyID::Normal;
   Info.DataLayer = EMapDataLayer::Hotel;
   NextAnomalyData = Info;
}

void UAnomalyGeneratorSubsystem::ApplyNormalFloor()
{
   auto* VerdictSubsystem = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();
   CurrentAnomaly = nullptr;
   VerdictSubsystem->SetNoAnomalyState();
   NextAnomalyData = DecideNext();
}

void UAnomalyGeneratorSubsystem::NotifySpawned()
{
   if (bIsInitialFloor)
   {
      bIsInitialFloor = false;
      return;
   }
   GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>()->OnAnomalyStateChanged.Broadcast();
}

TOptional<FAnomalySpawnInfo> UAnomalyGeneratorSubsystem::DecideAnomaly(uint8 Index) const
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
   if (!bHasAnomaly)
   {
      return TOptional<FAnomalySpawnInfo>();
   }

   const FAnomalyEntry& Data = AssetManager.GetActAnomalyByIndex(Index);

   FAnomalySpawnInfo Info;
   Info.AnomalyID = Data.ID;
   Info.Rule = Data.Rule;
   Info.DataLayer = Data.DataLayer;
   Info.EventClass = Data.Event;

   return Info;
}

TOptional<FAnomalySpawnInfo> UAnomalyGeneratorSubsystem::DecideNext() const
{
   const auto* GI = GetGameInstance();
   const auto* AnomalySub = GI->GetSubsystem<UAnomalyPoolSubsystem>();
   const auto* FloorSub = GI->GetSubsystem<UFloorProgressSubsystem>();
   constexpr int32 NormalChance = 15; 
   if(FMath::RandRange(1, 100) <= NormalChance || FloorSub->GetFloor() == STARTFLOOR)
   {
      return TOptional<FAnomalySpawnInfo>();
   }
   return DecideAnomaly(AnomalySub->ActIndex);
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
   NextAnomalyData.Reset();
   const auto& AnomalyVerdictSys = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();
   AnomalyVerdictSys->SetNoAnomalyState();
   bIsInitialFloor = true;
}

#pragma endregion