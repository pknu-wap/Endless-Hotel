// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly_Generator.h"
#include "Anomaly/Event/Anomaly_Event.h"
#include "Asset/DataAsset/Anomaly/PDA_Anomaly.h"
#include "Asset/Manager/EHAssetManager.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "GameSystem/SubSystem/AnomalyPoolSubsystem.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include <EngineUtils.h>

#pragma region AnomalyObject

void AAnomaly_Generator::AnomalyObjectLinker(const TArray<TSubclassOf<AAnomaly_Object_Base>>& TargetClasses)
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

void AAnomaly_Generator::BeginPlay()
{
	Super::BeginPlay();
	auto* FloorSub = GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>();
	FloorSub->FloorChange_Reset.AddUniqueDynamic(this, &ThisClass::SpawnAnomaly);
	bIsInitialFloor = true;
}

#pragma endregion

#pragma region Spawn

void AAnomaly_Generator::SpawnAnomaly()
{
	auto* FloorSubsystem = GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>();
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
	}
	UEHGameInstance* GameInstance = GetWorld()->GetGameInstance<UEHGameInstance>();
	CurrentAnomaly = SpawnFromInfo(CurrentData, GetLevel());

	TArray<TSubclassOf<AAnomaly_Object_Base>> TargetClasses = AssetManager.GetObjectByID(CurrentAnomaly->AnomalyID);
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

FAnomalySpawnInfo AAnomaly_Generator::DecideAnomaly(uint8 Index, bool bForceNormal)
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
	Info.DataLayer = Data.DataLayer;
	Info.EventClass = Data.Event;

	return Info;
}

FAnomalySpawnInfo AAnomaly_Generator::DecideNext()
{
	auto* AnomalySub = GetGameInstance()->GetSubsystem<UAnomalyPoolSubsystem>();
	constexpr int32 NormalChance = 15;
	const bool bForceNormal = FMath::RandRange(1, 100) <= NormalChance;

	return DecideAnomaly(AnomalySub->ActIndex, bForceNormal);
}

AAnomaly_Event* AAnomaly_Generator::SpawnFromInfo(const FAnomalySpawnInfo& Info, ULevel* SpawnLevel)
{
	UClass* AnomalyClass = Info.EventClass.LoadSynchronous();
	if (!IsValid(AnomalyClass))
	{
		return nullptr;
	}

	FActorSpawnParameters Params;
	Params.OverrideLevel = SpawnLevel;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AAnomaly_Event* Spawned = GetWorld()->SpawnActor<AAnomaly_Event>(AnomalyClass, FTransform::Identity, Params);

	if (Spawned)
	{
		Spawned->AnomalyID = Info.AnomalyID;
	}
	return Spawned;
}

bool AAnomaly_Generator::SetNextAnomalyForced(EAnomalyID ID)
{
	auto& AssetManager = UEHAssetManager::Get();
	auto* VerdictSub = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();

	FAnomalyEntry Data;
	if (!AssetManager.TryGetActAnomalyEntryByID(ID, Data))
	{
		UE_LOG(LogTemp, Warning, TEXT("[Anomaly_Generator] SetNextAnomalyForced failed: ID not in active pool."));
		return false;
	}

	FAnomalySpawnInfo Info;
	Info.bIsNormal = false;
	Info.AnomalyID = Data.ID;
	Info.DataLayer = Data.DataLayer;
	Info.EventClass = Data.Event;

	NextAnomalyData = Info;
	VerdictSub->SetNextAnomaly(NextAnomalyData->AnomalyID, NextAnomalyData->DataLayer);
	VerdictSub->NextAnomalyID = ID;

	return true;
}

#pragma endregion