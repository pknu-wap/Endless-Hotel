// Copyright by 2025-2 WAP Game 2 team

#include "AnomalyProgressSubSystem.h"
#include "GameSystem/Anomaly/Anomaly_Generator.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Data/Anomaly/AnomalyData.h"
#include "Anomaly/Base/Anomaly_Base.h"

#pragma region Base

UAnomalyProgressSubSystem::UAnomalyProgressSubSystem(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UDataTable> AnomalyFinder(TEXT("/Game/EndlessHotel/Data/DT_AnomalyData.DT_AnomalyData"));
	if (AnomalyFinder.Succeeded())
	{
		DataTable_Anomaly = AnomalyFinder.Object;
	}
}

#pragma endregion

#pragma region Verdict

bool UAnomalyProgressSubSystem::ComputeVerdict(bool bSolved, bool bNormalElevator) const
{
	switch (VerdictMode)
	{
	case EAnomalyVerdictMode::AnomalyElevatorOnly:
		return !bNormalElevator;
	case EAnomalyVerdictMode::SolvedOnly:
		return bSolved;
	case EAnomalyVerdictMode::Both_AND:
		return bSolved && !bNormalElevator;
	case EAnomalyVerdictMode::Either_OR:
		return bSolved || bNormalElevator;
	default:
		return false;
	}
}

void UAnomalyProgressSubSystem::ApplyVerdict()
{
	const bool bPassed = ComputeVerdict(bIsAnomalySolved, bIsElevatorNormal);
	UE_LOG(LogTemp, Log, TEXT("[Verdict] Verdict Mode is %s, Verdict Result is %s"),
		*UEnum::GetValueAsString(VerdictMode), bPassed ? TEXT("Pass") : TEXT("FAIL"))
	if (bPassed) 
	{
		SubFloor();
		if(!AnomalyHistory.Contains(CurrentAnomalyID))
		{
			AnomalyHistory.Add(CurrentAnomalyID);
		}
		AnomalyCount++;
	}
	else 
	{ 
		SetFloor(); 
	}
	bIsAnomalySolved = false;
}

#pragma endregion

#pragma region Floor

void UAnomalyProgressSubSystem::SetFloor()
{
	Floor = 9;
	return;
}

void UAnomalyProgressSubSystem::SubFloor()
{
	if (Floor > 1)
	{
		Floor--;
	}
	return;
}

void UAnomalyProgressSubSystem::AddFloor()
{
	if (Floor < 9)
	{
		Floor++;
	}
	return;
}

#pragma endregion

#pragma region AnomalyGenerate

void UAnomalyProgressSubSystem::AnomalySpawn()
{
	AAnomaly_Generator* Generator = nullptr;

	for (TActorIterator<AAnomaly_Generator> GeneratorInWorld(GetWorld()); GeneratorInWorld; ++GeneratorInWorld)
	{
		Generator = *GeneratorInWorld;
		break;
	}

	Generator->SpawnAnomalyAtIndex(ActIndex, true);
	ActIndex++;
}

#pragma endregion

#pragma region AnomalyDataBase

void UAnomalyProgressSubSystem::GetAnomalyData()
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
				OriginAnomaly.Add({ LoadedClass, (uint8)Data->AnomalyID });
			}
		}
	}
}

uint8 UAnomalyProgressSubSystem::GetAnomalyDataByID(uint8 AnomalyID)
{
	if (const FAnomalyData* Data = DataTable_Anomaly->FindRow<FAnomalyData>(*FString::FromInt(AnomalyID), TEXT("")))
	{
		return Data->Object_ID;
	}
	return -1;
}

#pragma endregion

#pragma region Pool & Reset

void UAnomalyProgressSubSystem::InitializePool(bool bShuffle)
{
	// Copy from Original
	ActAnomaly = OriginAnomaly;

	// Shuffle
	if (bShuffle && ActAnomaly.Num() > 1)
	{
		for (int32 CurrentIndex = ActAnomaly.Num() - 1; CurrentIndex > 0; --CurrentIndex)
		{
			const int32 RandomIndex = FMath::RandRange(0, CurrentIndex);
			if (CurrentIndex != RandomIndex)
			{
				ActAnomaly.Swap(CurrentIndex, RandomIndex);
			}
		}
	}

	// Reset Index
	ActIndex = 0;
}

void UAnomalyProgressSubSystem::ResetSequence(bool bShuffle)
{
	InitializePool(true);
}

#pragma endregion