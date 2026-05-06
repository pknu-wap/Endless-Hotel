// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Neapolitan/Radio/Anomaly_Radio.h"
#include "Anomaly/Object/Neapolitan/Radio/Anomaly_Object_Radio.h"

#pragma region Activity

void AAnomaly_Radio::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyID::Radio:
		SetupAnomalyAction(&AAnomaly_Object_Radio::PointerMoving, { EInteractType::TurnOff });
		ScheduleAnomaly(20);
		break;
	}
}

#pragma endregion