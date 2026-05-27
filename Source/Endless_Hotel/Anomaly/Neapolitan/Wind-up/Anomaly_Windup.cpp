// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Neapolitan/Wind-up/Anomaly_Windup.h"
#include "Anomaly/Object/Neapolitan/Wind-up/Anomaly_Object_Windup.h"

#pragma region Activity

void AAnomaly_Windup::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyID::Windup:
		SetupAnomalyAction(&AAnomaly_Object_Windup::StartWindupLoop, { EInteractType::TurnOff, EInteractType::Burn });
		ScheduleAnomaly(20);
		break;
	}
}

#pragma endregion