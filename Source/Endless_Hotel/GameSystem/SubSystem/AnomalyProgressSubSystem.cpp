// Copyright by 2025-2 WAP Game 2 team

#include "AnomalyProgressSubSystem.h"
#include "GameSystem/Anomaly/Anomaly_Generator.h"
#include "Engine/World.h"
#include "EngineUtils.h"

#pragma region AnomalyState

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
			UE_LOG(LogTemp, Log, TEXT("[Verdict] New Verdict Found"));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("[Verdict] Verdict Already Found Before"));
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
	UE_LOG(LogTemp, Log, TEXT("[AnomalySubsystem] Floor set to %d"), Floor);
	return;
}

void UAnomalyProgressSubSystem::SubFloor()
{
	if (Floor > 1)
	{
		Floor--;
		UE_LOG(LogTemp, Log, TEXT("[AnomalySubsystem] Floor decreased to %d"), Floor);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[AnomalySubsystem] Floor is already at minimum (1). Cannot decrease further."));
	}
	return;
}

void UAnomalyProgressSubSystem::AddFloor()
{
	if (Floor < 9)
	{
		Floor++;
		UE_LOG(LogTemp, Log, TEXT("[AnomalySubsystem] Floor increased to %d"), Floor);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[AnomalySubsystem] Floor is already at maximum (9). Cannot increase further."));
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

	if (!Generator)
	{
		UE_LOG(LogTemp, Warning, TEXT("[AnomalySubsystem] No AAnomaly_Generator found in level."));
		return;
	}

	Generator->SpawnNextAnomaly(true);
}

#pragma endregion
