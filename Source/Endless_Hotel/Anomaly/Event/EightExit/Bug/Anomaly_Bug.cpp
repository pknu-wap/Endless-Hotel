// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/Bug/Anomaly_Bug.h"
#include <NiagaraFunctionLibrary.h>
#include <NiagaraComponent.h>

#pragma region Activity

void AAnomaly_Bug::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyID)
	{
	case EAnomalyID::Bug:
		SetupAnomalyAction<ThisClass>(&ThisClass::SpawnBugs);
		ScheduleAnomaly();
		break;
	}
}

void AAnomaly_Bug::DisableAnomaly()
{
	for (auto Target : SpawnedBugs)
	{
		Target->DestroyComponent();
	}

	SpawnedBugs.Empty();

	Super::DisableAnomaly();
}

#pragma endregion

#pragma region Bug

void AAnomaly_Bug::SpawnBugs()
{
	auto* NS_Long =	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_BugLong, FVector(-2025.0, 571.0, 728.5), FRotator::ZeroRotator);

	SpawnedBugs.Add(NS_Long);

	auto* NS_Short = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_BugShort, FVector(-3110.0, 224.0, 728.5), FRotator::ZeroRotator);

	SpawnedBugs.Add(NS_Short);
}

#pragma endregion