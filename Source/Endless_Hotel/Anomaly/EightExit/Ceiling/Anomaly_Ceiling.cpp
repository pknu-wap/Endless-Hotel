// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Ceiling/Anomaly_Ceiling.h"
#include "Anomaly/Object/EightExit/Ceiling/Anomaly_Object_Ceiling.h"

#pragma region Activity

void AAnomaly_Ceiling::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyName::Ceil_Rotate:
		AnomalyAction = MakeAnomalyAction(&AAnomaly_Object_Ceiling::PlayCeilingRotate);
		ScheduleAnomaly(10.0f);
		break;

	case EAnomalyName::Ceil_Blood:
		AnomalyAction = MakeAnomalyAction(&AAnomaly_Object_Ceiling::CeilingBloodDripping);
		ScheduleAnomaly(10.0f);
		break;
	}
	
}

#pragma endregion