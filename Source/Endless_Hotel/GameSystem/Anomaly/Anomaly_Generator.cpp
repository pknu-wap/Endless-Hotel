// Anomaly_Generator.cpp

#include "Anomaly_Generator.h"
#include "Kismet/GameplayStatics.h"
#include "HAL/PlatformTime.h"
#include "Misc/DateTime.h"
#include "Misc/Guid.h"

AAnomaly_Generator::AAnomaly_Generator(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAnomaly_Generator::BeginPlay()
{
	Super::BeginPlay();

	InitializePool(true);

	// Check DefaultID Settings
	TSet<int32> Used;
	for (auto Cls : Act_Anomaly)
	{
		if (!*Cls) continue;
		const AAnomaly_Base_Ex* CDO = Cls->GetDefaultObject<AAnomaly_Base_Ex>();
		const int32 FixedID = CDO ? CDO->DefaultID : -1;

		if (FixedID < 0)
		{
			UE_LOG(LogTemp, Warning,
				TEXT("[Anomaly_Generator] %s DefaultID not set."),
				*GetNameSafe(Cls));
		}
		else if (Used.Contains(FixedID))
		{
			UE_LOG(LogTemp, Error,
				TEXT("[Anomaly_Generator] Duplicate DefaultID=%d on class %s"),
				FixedID, *GetNameSafe(Cls));
		}
		else
		{
			Used.Add(FixedID);
		}
	}

	// For Test
	SpawnNextAnomaly();
	SpawnNextAnomaly();
	SpawnNextAnomaly();
	SpawnNextAnomaly();
}

int32 AAnomaly_Generator::MakeTimeSeed()
{
	const int64 Ticks = FDateTime::UtcNow().GetTicks();
	const uint64 Cycles = FPlatformTime::Cycles64();
	const FGuid Guid = FGuid::NewGuid();
	const uint64 Mix = ((uint64)Guid.A << 32) ^ Guid.D;
	const uint64 Combo = ((uint64)Ticks) ^ Cycles ^ Mix;
	return (int32)(Combo & 0xFFFFFFFF);
}

// Reset Pool
void AAnomaly_Generator::InitializePool(bool bShuffle)
{
	// Seed by Time
	Seed = MakeTimeSeed();

	// Reset Stream
	RS.Initialize(Seed);

	// Copy from Original
	Act_Anomaly = Origin_Anomaly;

	// Shuffle
	if (bShuffle && Act_Anomaly.Num() > 1)
	{
		for (int32 i = Act_Anomaly.Num() - 1; i > 0; --i)
		{
			const int32 j = RS.RandRange(0, i);
			if (i != j)
			{
				Act_Anomaly.Swap(i, j);
			}
		}
	}

	// Reset Index
	Current_AnomalyID = -1;

	UE_LOG(LogTemp, Log, TEXT("[Anomaly_Generator] InitializePool: Seed=%d, Count=%d"),
		Seed, Act_Anomaly.Num());
}

void AAnomaly_Generator::ResetSequence(bool bShuffle)
{
	InitializePool(bShuffle);
}

// Pick Random Spawn Transform
// Anomaly_Generator.cpp
FTransform AAnomaly_Generator::PickSpawnTransform() const
{
	if (SpawnPoints.IsValidIndex(SpawnIndex))
	{
		return SpawnPoints[SpawnIndex];
	}
	return FTransform::Identity;
}


// Spawn Next Anomaly
AAnomaly_Base_Ex* AAnomaly_Generator::SpawnNextAnomaly(bool bDestroyPrev)
{
	const int32 NextIndex = Current_AnomalyID + 1;
	return SpawnAnomalyAtIndex(NextIndex, bDestroyPrev);
}

bool AAnomaly_Generator::DestroyCurrentAnomaly()
{
	if (CurrentAnomaly.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("[Anomaly_Generator] Destroying %s"), *CurrentAnomaly->GetName());
		CurrentAnomaly->Destroy();
		CurrentAnomaly = nullptr;
		return true;
	}
	return false;
}

// Spawn Anomaly at Specific Index
AAnomaly_Base_Ex* AAnomaly_Generator::SpawnAnomalyAtIndex(int32 Index, bool bDestroyPrev)
{
	UE_LOG(LogTemp, Verbose, TEXT("[Gen %s] SpawnAnomalyAtIndex(%d)"), *GetName(), Index);

	// Origin Empty Check
	if (Origin_Anomaly.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Anomaly_Generator] Origin_Anomaly is empty."));
		return nullptr;
	}

	// Out of Range Check
	if (!Act_Anomaly.IsValidIndex(Index))
	{
		UE_LOG(LogTemp, Log, TEXT("[Anomaly_Generator] Sequence ended. Re-initializing pool..."));
		InitializePool(true);

		if (Act_Anomaly.Num() == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("[Anomaly_Generator] Act_Anomaly is empty after re-init."));
			return nullptr;
		}

		Index = 0; // restart
	}

	// Destroy Previous
	if (bDestroyPrev)
	{
		DestroyCurrentAnomaly();
	}

	TSubclassOf<AAnomaly_Base_Ex> Cls = Act_Anomaly[Index];
	if (!*Cls)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Anomaly_Generator] Invalid class at index %d"), Index);
		return nullptr;
	}

	// Spawn
	const FTransform SpawnTM = PickSpawnTransform();

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AAnomaly_Base_Ex* Spawned =
		GetWorld()->SpawnActor<AAnomaly_Base_Ex>(Cls, SpawnTM, Params);

	if (!Spawned)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Anomaly_Generator] Spawn failed at index %d"), Index);
		return nullptr;
	}

	// Setting Fixed ID
	const AAnomaly_Base_Ex* CDO = Cls->GetDefaultObject<AAnomaly_Base_Ex>();
	const int32 FixedID = (CDO ? CDO->DefaultID : -1);

	if (FixedID < 0)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("[Anomaly_Generator] %s has no DefaultID set (stays -1)."),
			*GetNameSafe(Cls));
	}

	// Start
	Spawned->StartAnomaly();

	Current_AnomalyID = Index;
	CurrentAnomaly = Spawned;

	// EventBroadCast
	OnAnomalySpawned.Broadcast(Spawned);

	return Spawned;
}
