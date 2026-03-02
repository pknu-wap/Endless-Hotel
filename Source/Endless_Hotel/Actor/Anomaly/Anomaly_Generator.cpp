// Anomaly_Generator.cpp

#include "Anomaly_Generator.h"
#include "Anomaly/Base/Anomaly_Event.h"
#include "Data/Anomaly/AnomalyData.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "Data/Controller/DataController.h"
#include <Kismet/GameplayStatics.h>

#pragma region AnomalyObjectLinker

void AAnomaly_Generator::AnomalyObjectLinker()
{
	auto* DataC = GetGameInstance()->GetSubsystem<UDataController>();

	TArray<TSubclassOf<AAnomaly_Object_Base>> TargetClasses = DataC->GetObjectByID(CurrentAnomaly->AnomalyID);
	
	if (TargetClasses.Num() == 0)
	{
		return;
	}

	for (TSubclassOf<AAnomaly_Object_Base> TargetClass : TargetClasses)
	{
		if (!TargetClass) continue;

		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), TargetClass, FoundActors);

		for (auto* FoundActor : FoundActors)
		{
			if (!IsValid(FoundActor) || FoundActor->GetLevel() != this->GetLevel())
			{
				continue;
			}

			auto* AnomalyObject = Cast<AAnomaly_Object_Base>(FoundActor);
			if (AnomalyObject)
			{
				AnomalyObject->AnomalyID = CurrentAnomaly->AnomalyID;
				AnomalyObject->SetInteraction();

				CurrentAnomaly->LinkedObjects.Add(FoundActor);
			}
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
		if (DataC->ActAnomaly.Num() == 0)
		{
			return nullptr;
		}
		Index = 0;
		Sub->InitializePool();
		return SpawnAnomalyAtIndex(Index, SpawnLevel); // restart
	}

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

	AnomalyObjectLinker();

	// Start
	Spawned->SetAnomalyState();

	// EventBroadCast
	OnAnomalySpawned.Broadcast(Spawned);
	Sub->CurrentAnomalyID = Spawned->AnomalyID;
	Sub->CurrentAnomaly = Spawned;
	return Spawned;
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