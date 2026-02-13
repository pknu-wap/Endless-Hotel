// Anomaly_Generator.cpp

#include "Anomaly_Generator.h"
#include "Anomaly/Base/Anomaly_Base.h"
#include "Data/Anomaly/AnomalyData.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"
#include "Data/Controller/DataController.h"
#include <Kismet/GameplayStatics.h>

#pragma region AnomalyObjectLinker

void AAnomaly_Generator::AnomalyObjectLinker()
{
	auto* DataC = GetGameInstance()->GetSubsystem<UDataController>();

	UClass* TargetClass = DataC->GetObjectByID(CurrentAnomaly->AnomalyID);
	
	if (!TargetClass)
	{
		return;
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TargetClass, OUT FoundActors);

	for (auto* FoundActor : FoundActors)
	{
		if (!IsValid(FoundActor) || FoundActor->GetLevel() != this->GetLevel())
		{
			continue;
		}


		auto* AnomalyObject = Cast<AAnomaly_Object_Base>(FoundActor);
		AnomalyObject->AnomalyID = CurrentAnomaly->AnomalyID;
		CurrentAnomaly->LinkedObjects.Add(FoundActor);
		AnomalyObject->SetInteraction();
	}
}

#pragma endregion

#pragma region Generate

// Spawn Anomaly at Specific Index
AAnomaly_Base* AAnomaly_Generator::SpawnAnomalyAtIndex(uint8 Index, ULevel* SpawnLevel)
{
	UE_LOG(LogTemp, Verbose, TEXT("[Gen %s] SpawnAnomalyAtIndex(%d)"), *GetName(), Index);

	auto* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
	auto* DataC = GetGameInstance()->GetSubsystem<UDataController>();

	// Out of Range Check
	if (!(DataC->ActAnomaly).IsValidIndex(Index))
	{
		if (DataC->ActAnomaly.Num() == 0)
		{
			return nullptr;
		}
		Index = 0;
		Sub->InitializePool();
		return SpawnAnomalyAtIndex(Index, SpawnLevel); // restart
	}

	TSubclassOf<AAnomaly_Base> AnomalyClass = DataC->ActAnomaly[Index].AnomalyClass;

	// Spawn
	const FTransform SpawnTransform(FVector::ZeroVector);

	FActorSpawnParameters Params;
	Params.OverrideLevel = SpawnLevel;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AAnomaly_Base* Spawned =
		GetWorld()->SpawnActor<AAnomaly_Base>(AnomalyClass, SpawnTransform, Params);

	if (!Spawned)
	{
		return nullptr;
	}

	Spawned->AnomalyID = DataC->ActAnomaly[Index].AnomalyID;

	CurrentAnomaly = Spawned;

	AnomalyObjectLinker();

	// Start
	Spawned->SetAnomalyActivate();

	// EventBroadCast
	OnAnomalySpawned.Broadcast(Spawned);
	Sub->CurrentAnomalyID = Spawned->AnomalyID;
	Sub->CurrentAnomaly = Spawned;
	return Spawned;
}

AAnomaly_Base* AAnomaly_Generator::SpawnNormal(ULevel* SpawnLevel)
{
	auto* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();

	TSubclassOf<AAnomaly_Base> AnomalyClass = NormalClass;

	// Spawn
	const FTransform SpawnTransform(FVector::ZeroVector);

	FActorSpawnParameters Params;
	Params.OverrideLevel = SpawnLevel;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AAnomaly_Base* Spawned =
		GetWorld()->SpawnActor<AAnomaly_Base>(AnomalyClass, SpawnTransform, Params);

	if (!Spawned)
	{
		return nullptr;
	}

	CurrentAnomaly = Spawned;
	Sub->CurrentAnomaly = Spawned;

	return Spawned;
}
#pragma endregion