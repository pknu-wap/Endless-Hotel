// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/SubSystem/AnomalyGeneratorSubsystem.h"
#include "GameSystem/SubSystem/AnomalyPoolSubsystem.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include "GameSystem/SubSystem/EHGameSystem.h"
#include "Anomaly/Event/Anomaly_Event.h"
#include "Asset/Manager/EHAssetManager.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"

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
   if (VerdictSubsystem->IsLobbyPhase())
   {
      if (VerdictSubsystem->GetNextAnomalyMap() == EMapDataLayer::Lobby)
      {
         VerdictSubsystem->SetNextAnomaly(EAnomalyID::None, EMapDataLayer::Hotel);
         return;
      }
      VerdictSubsystem->SetLobbyPhase(false);
   }

   const auto* GameSys = GetGameInstance()->GetSubsystem<UEHGameSystem>();
   if (GameSys && GameSys->GetGameProgression() == EGameProgression::CheckIn)
   {
      ApplyNormalFloor();
      return;
   }
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
   RollNext();
   NotifySpawned();
}

void UAnomalyGeneratorSubsystem::ForceNormalNext()
{
   NextAnomalyData = MakeNormalInfo();
}

void UAnomalyGeneratorSubsystem::ApplyNormalFloor()
{
   auto* VerdictSubsystem = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();
   CurrentAnomaly = nullptr;
   VerdictSubsystem->SetNoAnomalyState();
   RollNext();
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
   const auto* AnomalySub = GetGameInstance()->GetSubsystem<UAnomalyPoolSubsystem>();
   constexpr int32 NormalChance = 15;

   if (FMath::RandRange(1, 100) <= NormalChance)
   {
      return MakeNormalInfo();
   }

   TOptional<FAnomalySpawnInfo> Result = DecideAnomaly(AnomalySub->ActIndex);
   return Result.IsSet() ? Result : MakeNormalInfo();
}

void UAnomalyGeneratorSubsystem::RollNext()
{
   NextAnomalyData = DecideNext();

   auto* VerdictSubsystem = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();
   if (VerdictSubsystem && NextAnomalyData.IsSet())
   {
      VerdictSubsystem->SetNextAnomaly(NextAnomalyData->AnomalyID, NextAnomalyData->DataLayer);
   }
}

FAnomalySpawnInfo UAnomalyGeneratorSubsystem::MakeNormalInfo() const
{
   FAnomalySpawnInfo Info;
   Info.bIsNormal = true;
   Info.AnomalyID = EAnomalyID::Normal;
   Info.DataLayer = EMapDataLayer::Hotel;
   return Info;
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
   ForceNormalNext();
   bIsInitialFloor = true;
}

#pragma endregion