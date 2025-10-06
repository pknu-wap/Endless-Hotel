// Copyright by 2025-2 WAP Game 2 team

#include "AnomalyProgressSubSystem.h"
#include "GameSystem/Anomaly/Anomaly_Generator.h"
#include "Engine/World.h"
#include "EngineUtils.h"

#pragma region AnomalyState

void UAnomalyProgressSubSystem::SetIsAnomalySolved(bool bNewValue)
{
	bIsAnomalySolved = bNewValue;
}

void UAnomalyProgressSubSystem::SetIsElevatorNormal(bool bNewValue)
{
	bIsElevatorNormal = bNewValue;
}

#pragma endregion

#pragma region Verdict

void UAnomalyProgressSubSystem::AnomalyVerdict()
{
	if (bIsAnomalySolved)
	{
		UE_LOG(LogTemp, Log, TEXT("[AnomalySubsystem] Anomaly solved. Decreasing floor."));
		SubFloor();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("[AnomalySubsystem] Anomaly not solved. Resetting floor to 9."));
		SetFloor();
	}
	bIsAnomalySolved = false;
	return;
}

void UAnomalyProgressSubSystem::EvaluateElevatorChoice(bool bElevatorIsNormal)
{
	if (bIsAnomalySolved && !bElevatorIsNormal)
	{
		UE_LOG(LogTemp, Log, TEXT("[AnomalySubsystem] Solved + Abnormal elevator: PASS."));
		SubFloor();
	}
	else if (!bIsAnomalySolved && bElevatorIsNormal)
	{
		UE_LOG(LogTemp, Log, TEXT("[AnomalySubsystem] Not solved + Normal elevator: FAIL."));
		SetFloor();
	}
	return;
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
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("[AnomalySubsystem] World is null. Cannot spawn anomaly."));
		return;
	}

	AAnomaly_Generator* Gen = nullptr;

	for (TActorIterator<AAnomaly_Generator> It(World); It; ++It)
	{
		if (IsValid(*It))
		{
			Gen = *It;
			break;
		}
	}

	if (!IsValid(Gen))
	{
		UE_LOG(LogTemp, Warning, TEXT("[AnomalySubsystem] No AAnomaly_Generator found in level."));
		return;
	}

	Gen->SpawnNextAnomaly(true);
}

#pragma endregion
