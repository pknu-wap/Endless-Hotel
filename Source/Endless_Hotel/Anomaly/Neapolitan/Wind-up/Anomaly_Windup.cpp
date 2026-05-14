// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Neapolitan/Wind-up/Anomaly_Windup.h"

#pragma region Activity

void AAnomaly_Windup::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyID::Windup:
		ScheduleAnomaly(20);
		break;
	}
}

#pragma endregion