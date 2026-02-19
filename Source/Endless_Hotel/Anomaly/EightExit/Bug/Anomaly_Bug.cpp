// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Bug/Anomaly_Bug.h"
#include "Anomaly/Object/Bug/Anomaly_Object_Bug.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include <Engine/LevelStreamingDynamic.h>

#pragma region Activity

void AAnomaly_Bug::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();

	switch (AnomalyName)
	{
	case EAnomalyName::Bug:
		ActiveTrigger();
		break;
	}
}

void AAnomaly_Bug::StartAnomalyAction()
{
	SpawnBugs();
}

#pragma endregion

#pragma region Bug

void AAnomaly_Bug::SpawnBugs()
{
	FActorSpawnParameters Params;
	Params.OverrideLevel = GetGameInstance<UEHGameInstance>()->GetCurrentLevel()->GetLoadedLevel();

	for (const FVector& Target : BugLocations)
	{
		auto* SpawnedBug = GetWorld()->SpawnActor<AAnomaly_Object_Bug>(BugClass, Target, FRotator::ZeroRotator, Params);
		SpawnedBug->ActiveBug();
	}
}

#pragma endregion