// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/Disappear/Anomaly_Disappear.h"
#include "Anomaly/Object/EightExit/Disappear/Anomaly_Object_Disappear.h"


#pragma region Activity

void AAnomaly_Disappear::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyName::Disappear:
		SetupAnomalyAction(&AAnomaly_Object_Disappear::StartDisappear);
		ScheduleAnomaly();
		break;
	}
}

#pragma endregion