// Copyright by 2025-2 WAP Game 2 team


#include "AnomalyProgressSubSystem.h"

void UAnomalyProgressSubSystem::SetIsAnomalySolved(bool bNewValue)
{
	bIsAnomalySolved = bNewValue;
}

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
		// Exit
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
		// Exit
	}
	return;
}