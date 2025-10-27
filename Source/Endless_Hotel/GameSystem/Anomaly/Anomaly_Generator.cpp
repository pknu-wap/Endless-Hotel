// Anomaly_Generator.cpp

#include "Anomaly_Generator.h"
#include "Kismet/GameplayStatics.h"
#include "HAL/PlatformTime.h"
#include "Misc/DateTime.h"
#include "Misc/Guid.h"
#include "Anomaly/Base/Anomaly_Base.h"
#include "Data/Anomaly/AnomalyData.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"

#pragma region Base

AAnomaly_Generator::AAnomaly_Generator(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UDataTable> AnomalyFinder(TEXT("/Game/EndlessHotel/Data/DT_AnomalyData.DT_AnomalyData"));
	if (AnomalyFinder.Succeeded())
	{
		DataTable_Anomaly = AnomalyFinder.Object;
	}
}

void AAnomaly_Generator::BeginPlay()
{
	Super::BeginPlay();

	InitializePool(true);

	GetAnomalyData();

	// Check AnomalyID Settings
	TSet<int32> UsedID;
	for (auto AnomalyClass : Act_Anomaly)
	{
		if (!*AnomalyClass) continue;
		const AAnomaly_Base* CDO = AnomalyClass->GetDefaultObject<AAnomaly_Base>();
		const int32 FixedID = CDO ? CDO->AnomalyID : -1;

		if (FixedID < 0)
		{
			UE_LOG(LogTemp, Warning,
				TEXT("[Anomaly_Generator] %s AnomalyID not set."),
				*GetNameSafe(AnomalyClass));
		}
		else if (UsedID.Contains(FixedID))
		{
			UE_LOG(LogTemp, Error,
				TEXT("[Anomaly_Generator] Duplicate AnomalyID=%d on class %s"),
				FixedID, *GetNameSafe(AnomalyClass));
		}
		else
		{
			UsedID.Add(FixedID);
		}
	}
}

#pragma endregion

#pragma region AnomalyDataBase

void AAnomaly_Generator::GetAnomalyData()
{

	FAnomalyData* Data = nullptr;

	for (auto RowData : DataTable_Anomaly->GetRowMap())
	{
		Data = (FAnomalyData*)RowData.Value;

		if (!Data->AnomalyPath.IsEmpty())
		{
			UClass* LoadedClass = StaticLoadClass(AAnomaly_Base::StaticClass(), nullptr, *Data->AnomalyPath);

			if (LoadedClass)
			{
				Origin_Anomaly.Add(LoadedClass);
			}
		}
	}
}

int32 AAnomaly_Generator::GetAnomalyDataByID(int32 AnomalyID)
{
	if (const FAnomalyData* Data = DataTable_Anomaly->FindRow<FAnomalyData>(*FString::FromInt(AnomalyID), TEXT("")))
	{
		return Data->Object_ID;
	}
	return -1;
}

#pragma endregion

#pragma region AnomalyObjectLinker

void AAnomaly_Generator::AnomalyObjectLinker()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAnomaly_Object_Base::StaticClass(), OUT FoundActors);

	for (auto* FoundActor : FoundActors)
	{
		auto* AnomalyObject = Cast<AAnomaly_Object_Base>(FoundActor);
		int32 LinkObjectID = GetAnomalyDataByID(CurrentAnomaly->AnomalyID);
		if(LinkObjectID == AnomalyObject->ObjectID)
			CurrentAnomaly->LinkedObjects.Add(AnomalyObject);
	}
}

#pragma endregion


#pragma region Pool & Sequence
// Reset Pool
void AAnomaly_Generator::InitializePool(bool bShuffle)
{

	// Copy from Original
	Act_Anomaly = Origin_Anomaly;

	// Shuffle
	if (bShuffle && Act_Anomaly.Num() > 1)
	{
		for (int32 CurrentIndex = Act_Anomaly.Num() - 1; CurrentIndex > 0; --CurrentIndex)
		{
			const int32 RandomIndex = FMath::RandRange(0, CurrentIndex);
			if (CurrentIndex != RandomIndex)
			{
				Act_Anomaly.Swap(CurrentIndex, RandomIndex);
			}
		}
	}

	// Reset Index
	Current_AnomalyID = -1;

	UE_LOG(LogTemp, Log, TEXT("[Anomaly_Generator] InitializePool: Count=%d"),
		Act_Anomaly.Num());
}

void AAnomaly_Generator::ResetSequence(bool bShuffle)
{
	InitializePool(bShuffle);
}

#pragma endregion

#pragma region Generate

// Pick Random Spawn Transform
FTransform AAnomaly_Generator::PickSpawnTransform() const
{
	if (SpawnPoints.IsValidIndex(SpawnIndex))
	{
		return SpawnPoints[SpawnIndex];
	}
	return FTransform::Identity;
}

// Spawn Next Anomaly
AAnomaly_Base* AAnomaly_Generator::SpawnNextAnomaly(bool bDestroyPrev)
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
AAnomaly_Base* AAnomaly_Generator::SpawnAnomalyAtIndex(int32 Index, bool bDestroyPrev)
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

	TSubclassOf<AAnomaly_Base> AnomalyClass = Act_Anomaly[Index];
	if (!*AnomalyClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Anomaly_Generator] Invalid class at index %d"), Index);
		return nullptr;
	}

	// Spawn
	const FTransform SpawnTransform = PickSpawnTransform();

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AAnomaly_Base* Spawned =
		GetWorld()->SpawnActor<AAnomaly_Base>(AnomalyClass, SpawnTransform, Params);

	if (!Spawned)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Anomaly_Generator] Spawn failed at index %d"), Index);
		return nullptr;
	}

	// Setting Fixed ID
	const AAnomaly_Base* CDO = AnomalyClass->GetDefaultObject<AAnomaly_Base>();
	const int32 FixedID = (CDO ? CDO->AnomalyID : -1);

	if (FixedID < 0)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("[Anomaly_Generator] %s has no AnomalyID set (stays -1)."),
			*GetNameSafe(AnomalyClass));
	}

	// Start
	Spawned->ActivateAnomaly();

	Current_AnomalyID = Index;
	CurrentAnomaly = Spawned;

	AnomalyObjectLinker();

	// EventBroadCast
	OnAnomalySpawned.Broadcast(Spawned);

	return Spawned;
}

#pragma endregion