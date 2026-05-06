// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Bug/Anomaly_Bug.h"
#include "Anomaly/Object/EightExit/Bug/Anomaly_Object_Bug.h"
#include "GameSystem/GameInstance/EHGameInstance.h"

#pragma region Activity

void AAnomaly_Bug::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyID::Bug:
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
	auto* GameInstance = GetGameInstance<UEHGameInstance>();

	for (const FVector& Target : BugLocations)
	{
		auto* SpawnedBug = GameInstance->SpawnActor<AAnomaly_Object_Bug>(BugClass, Target);
		SpawnedBug->ActiveBug();
	}
}

#pragma endregion