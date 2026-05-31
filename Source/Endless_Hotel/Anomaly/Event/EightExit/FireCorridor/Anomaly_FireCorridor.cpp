// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Event/EightExit/FireCorridor/Anomaly_FireCorridor.h"

#pragma region Activity

void AAnomaly_FireCorridor::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyID::FireCorridor:
		ScheduleAnomaly();
		break;
	}
}

#pragma endregion