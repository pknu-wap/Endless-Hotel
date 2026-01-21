// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Bug/Anomaly_Bug.h"
#include <NiagaraFunctionLibrary.h>

#pragma region Activity

void AAnomaly_Bug::ActivateAnomaly()
{
	Super::ActivateAnomaly();

	switch (AnomalyName)
	{
	case EAnomalyName::Bug:
		AnomalyAction = ([this](AAnomaly_Object_Base* Object)
			{
				SpawnBugs();
			});
		ActiveTrigger();
		break;
	}
}

#pragma endregion

#pragma region Bug

void AAnomaly_Bug::SpawnBugs()
{
	for (FVector Target : BugLocations)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, NS_Bug, Target);
	}
}

#pragma endregion