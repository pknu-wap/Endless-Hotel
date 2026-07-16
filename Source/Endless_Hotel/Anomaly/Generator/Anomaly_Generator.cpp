// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly_Generator.h"
#include "Anomaly/Event/Anomaly_Event.h"
#include "Data/Anomaly/AnomalyData.h"
#include "Asset/DataAsset/Anomaly/PDA_Anomaly.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "Data/Controller/DataController.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include <EngineUtils.h>

#pragma region AnomalyObject

void AAnomaly_Generator::AnomalyObjectLinker(const TArray<TSubclassOf<AAnomaly_Object_Base>>& TargetClasses)
{
	if (TargetClasses.IsEmpty())
	{
		return;
	}

	auto* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
	auto ObjectPool = Sub->GetAnomalyObject();

	const EAnomalyID TargetAnomalyName = static_cast<EAnomalyID>(CurrentAnomaly->AnomalyName);

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
					AnomalyObject->SetAnomalyName(CurrentAnomaly->AnomalyName);
					CurrentAnomaly->LinkedObjects.Add(AnomalyObject);
				}
			}
		}
	}
}

void AAnomaly_Generator::BeginPlay()
{
	Super::BeginPlay();
	auto* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
	Sub->FloorChange_Reset.AddUniqueDynamic(this, &ThisClass::SpawnAnomaly);
	bIsInitialFloor = true;
	SpawnAnomaly();
}

#pragma endregion

#pragma region Spawn

void AAnomaly_Generator::SpawnAnomaly()
{
	auto* Subsystem = GetGameInstance()->GetSubsystem<UGameSystem>();
	auto* DataC = GetGameInstance()->GetSubsystem<UDataController>();
	
	FAnomalySpawnInfo CurrentData = NextAnomalyData.IsSet() ? NextAnomalyData.GetValue() : DecideNext();
	if (Subsystem->Floor == STARTFLOOR && !CurrentData.bIsNormal)
	{
		CurrentData.bIsNormal = true;
		CurrentData.AnomalyID = DataC->NormalAnomalyData.ID;
		CurrentData.DataLayer = DataC->NormalAnomalyData.DataLayer;
		CurrentData.EventClass = DataC->NormalAnomalyData.Event;
	}
	UEHGameInstance* GameInstance = GetWorld()->GetGameInstance<UEHGameInstance>();
	CurrentAnomaly = SpawnFromInfo(CurrentData, GetLevel());

	TArray<TSubclassOf<AAnomaly_Object_Base>> TargetClasses = DataC->GetObjectByID(CurrentAnomaly->AnomalyName);
	AnomalyObjectLinker(TargetClasses);
	Subsystem->SetCurrentAnomaly(CurrentAnomaly, CurrentAnomaly->AnomalyName, CurrentData.DataLayer);
	NextAnomalyData = DecideNext();
	Subsystem->SetNextAnomaly(NextAnomalyData->AnomalyID, NextAnomalyData->DataLayer);
	if (bIsInitialFloor)
	{
		bIsInitialFloor = false;
	}
	else
	{
		Subsystem->OnAnomalySpawned.Broadcast();
	}
}

FAnomalySpawnInfo AAnomaly_Generator::DecideAnomaly(uint8 Index, bool bForceNormal)
{
	auto* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
	auto* DataC = GetGameInstance()->GetSubsystem<UDataController>();
	bool bHasAnomaly = DataC->ActAnomaly.IsValidIndex(Index);

	if (!bHasAnomaly)
	{
		Sub->InitializePool();
		Index = Sub->ActIndex;
		bHasAnomaly = DataC->ActAnomaly.IsValidIndex(Index);
	}
	const FAnomalyEntry& Data = bForceNormal || !bHasAnomaly ? DataC->NormalAnomalyData : DataC->ActAnomaly[Index];

	FAnomalySpawnInfo Info;
	Info.bIsNormal = bForceNormal || !bHasAnomaly;
	Info.AnomalyID = Data.ID;
	Info.DataLayer = Data.DataLayer;
	Info.EventClass = Data.Event;

	return Info;
}

FAnomalySpawnInfo AAnomaly_Generator::DecideNext()
{
	auto* Subsystem = GetGameInstance()->GetSubsystem<UGameSystem>();
	constexpr int32 NormalChance = 15;
	const bool bForceNormal = FMath::RandRange(1, 100) <= NormalChance;

	return DecideAnomaly(Subsystem->ActIndex, bForceNormal);
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
		Spawned->AnomalyName = Info.AnomalyID;
	}
	return Spawned;
}

#pragma endregion