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
	if (Subsystem->Floor == STARTFLOOR)
	{
		CurrentData.bIsNormal = true;
		CurrentData.DataLayer = EMapDataLayer::Hotel;
		CurrentData.AnomalyID = EAnomalyID::Normal;
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

FAnomalySpawnInfo AAnomaly_Generator::DecideAnomaly(uint8 Index)
{
	auto* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
	auto* DataC = GetGameInstance()->GetSubsystem<UDataController>();
	if (!DataC->ActAnomaly.IsValidIndex(Index))
	{
		Sub->InitializePool();
		return DecideAnomaly(0);
	}
	FAnomalySpawnInfo Info;
	Info.bIsNormal = false;
	Info.Index = Index;
	Info.AnomalyID = DataC->ActAnomaly[Index].ID;
	Info.DataLayer = DataC->ActAnomaly[Index].DataLayer;
	return Info;
}

FAnomalySpawnInfo AAnomaly_Generator::DecideNext()
{
	auto* Subsystem = GetGameInstance()->GetSubsystem<UGameSystem>();
	int32 IsNormal = FMath::RandRange(1, 100);

	if (IsNormal > 85)
	{
		FAnomalySpawnInfo Info;
		Info.bIsNormal = true;
		Info.AnomalyID = EAnomalyID::None;
		Info.DataLayer = EMapDataLayer::Hotel;
		return Info;
	}

	return DecideAnomaly(Subsystem->ActIndex);
}

AAnomaly_Event* AAnomaly_Generator::SpawnFromInfo(const FAnomalySpawnInfo& Info, ULevel* SpawnLevel)
{
	UClass* AnomalyClass;
	if (Info.bIsNormal)
	{
		AnomalyClass = NormalClass.LoadSynchronous();
	}
	else
	{
		auto* DataC = GetGameInstance()->GetSubsystem<UDataController>();
		TSoftClassPtr<AAnomaly_Event> SoftClass = DataC->ActAnomaly[Info.Index].Event;
		AnomalyClass = SoftClass.LoadSynchronous();

		if (!IsValid(AnomalyClass))
		{
			FTimerHandle RetryHandle;
			GetWorld()->GetTimerManager().SetTimer(RetryHandle,
				FTimerDelegate::CreateWeakLambda(this, [this, Info, SpawnLevel]()
					{
						SpawnFromInfo(Info, SpawnLevel);
					}), 0.5f, false);
			return nullptr;
		}
	}

	const FTransform SpawnTransform(FVector::ZeroVector);
	FActorSpawnParameters Params;
	Params.OverrideLevel = SpawnLevel;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AAnomaly_Event* Spawned = GetWorld()->SpawnActor<AAnomaly_Event>(AnomalyClass, SpawnTransform, Params);
	if (!Spawned)
	{
		return nullptr;
	}

	Spawned->AnomalyName = Info.AnomalyID;
	return Spawned;
}

#pragma endregion