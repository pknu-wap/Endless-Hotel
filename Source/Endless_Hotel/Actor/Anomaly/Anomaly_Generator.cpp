// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly_Generator.h"
#include "Anomaly/Base/Anomaly_Event.h"
#include "Data/Anomaly/AnomalyData.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "Data/Controller/DataController.h"
#include <EngineUtils.h>

#pragma region AnomalyObject

void AAnomaly_Generator::SpawnAnomalyObject(uint8 AnomalyID, FTransform SpawnTransform, FActorSpawnParameters Params)
{
	auto* DataC = GetGameInstance()->GetSubsystem<UDataController>();
	TArray<TSubclassOf<AAnomaly_Object_Base>> TargetClasses = DataC->GetObjectByID(AnomalyID);

	if (TargetClasses.IsEmpty())
	{
		return;
	}

	for (auto& ObjClass : TargetClasses)
	{
		if (!ObjClass)
		{
			continue;
		}

		auto* NewObj = GetWorld()->SpawnActor<AAnomaly_Object_Base>(ObjClass, SpawnTransform, Params);

		if (NewObj)
		{
			NewObj->AnomalyID = AnomalyID;
			NewObj->SetAnomalyName();

			CurrentAnomaly->LinkedObjects.Add(NewObj);
		}
	}
}

void AAnomaly_Generator::AnomalyObjectLinker()
{
	auto* DataC = GetGameInstance()->GetSubsystem<UDataController>();

	TArray<TSubclassOf<AAnomaly_Object_Base>> TargetClasses = DataC->GetObjectByID(CurrentAnomaly->AnomalyID);
	
	if (TargetClasses.IsEmpty())
	{
		return;
	}

	for (TActorIterator<AAnomaly_Object_Base> Iter(GetWorld()); Iter; ++Iter)
	{
		auto* AnomalyObject = *Iter;

		if (!IsValid(AnomalyObject) || AnomalyObject->GetLevel() != this->GetLevel())
		{
			continue;
		}

		if (TargetClasses.Contains(AnomalyObject->GetClass()))
		{
			AnomalyObject->AnomalyID = CurrentAnomaly->AnomalyID;
			AnomalyObject->SetAnomalyName();

			CurrentAnomaly->LinkedObjects.Add(AnomalyObject);
		}
	}
}

#pragma endregion

#pragma region Generate

// Spawn Anomaly at Specific Index
AAnomaly_Event* AAnomaly_Generator::SpawnAnomalyAtIndex(uint8 Index, ULevel* SpawnLevel)
{
	auto* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
	auto* DataC = GetGameInstance()->GetSubsystem<UDataController>();

	// Out of Range Check
	if (!(DataC->ActAnomaly).IsValidIndex(Index))
	{
		Index = 0;
		Sub->InitializePool();
		return SpawnAnomalyAtIndex(Index, SpawnLevel); // restart
	}

	UE_LOG(LogTemp, Log, TEXT("[GameSystem] RemainAnomaly: %d"), DataC->GetRemainingAnomalyCounts());
	TSoftClassPtr<AAnomaly_Event> SoftAnomalyClass = DataC->ActAnomaly[Index].AnomalyClass;
	UClass* AnomalyClass = SoftAnomalyClass.LoadSynchronous();

	if (!IsValid(AnomalyClass))
	{
		FTimerHandle RetryHandle;
		GetWorld()->GetTimerManager().SetTimer(RetryHandle, FTimerDelegate::CreateWeakLambda(this, [this, Index, SpawnLevel]()
			{
				this->SpawnAnomalyAtIndex(Index, SpawnLevel);
			}), 0.5f, false);

		return nullptr;
	}

	UE_LOG(LogTemp, Warning, TEXT("클래스 이름: %s"), *AnomalyClass->GetName());

	// Spawn
	const FTransform SpawnTransform(FVector::ZeroVector);

	FActorSpawnParameters Params;
	Params.OverrideLevel = SpawnLevel;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AAnomaly_Event* Spawned = GetWorld()->SpawnActor<AAnomaly_Event>(AnomalyClass, SpawnTransform, Params);

	if (!Spawned)
	{
		return nullptr;
	}

	Spawned->AnomalyID = DataC->ActAnomaly[Index].AnomalyID;
	CurrentAnomaly = Spawned;

	TArray<TSubclassOf<AAnomaly_Object_Base>> TargetClasses = DataC->GetObjectByID(CurrentAnomaly->AnomalyID);

	if (Spawned->bIsRuntimeSpawned)
	{
		SpawnAnomalyObject(CurrentAnomaly->AnomalyID, CurrentAnomaly->ObjectTransform, Params);
	}
	else
	{
		AnomalyObjectLinker();
	}

	// Start
	CurrentAnomaly->SetAnomalyState();

	// EventBroadCast
	OnAnomalySpawned.Broadcast(CurrentAnomaly);
	Sub->CurrentAnomalyID = CurrentAnomaly->AnomalyID;
	Sub->CurrentAnomaly = CurrentAnomaly;
	return CurrentAnomaly;
}

AAnomaly_Event* AAnomaly_Generator::SpawnNormal(ULevel* SpawnLevel)
{
	auto* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();

	UClass* AnomalyClass = NormalClass.LoadSynchronous();
	// Spawn
	const FTransform SpawnTransform(FVector::ZeroVector);

	FActorSpawnParameters Params;
	Params.OverrideLevel = SpawnLevel;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AAnomaly_Event* Spawned = GetWorld()->SpawnActor<AAnomaly_Event>(AnomalyClass, SpawnTransform, Params);

	if (!Spawned)
	{
		return nullptr;
	}

	CurrentAnomaly = Spawned;
	Sub->CurrentAnomaly = Spawned;

	return Spawned;
}

#pragma endregion