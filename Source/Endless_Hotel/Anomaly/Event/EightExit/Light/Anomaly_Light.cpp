// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/Light/Anomaly_Light.h"
#include "Anomaly/Object/EightExit/Light/Anomaly_Object_Light.h"

#pragma region Activity

void AAnomaly_Light::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyID)
	{
	case EAnomalyID::Light_Destroy:
		SetupAnomalyAction<AAnomaly_Object_Light>(&AAnomaly_Object_Light::StartDropLight);
		ActiveTrigger();
		break;

	case EAnomalyID::Light_Blue:
		SetupAnomalyAction<AAnomaly_Object_Light>(&AAnomaly_Object_Light::ChangeLightColor);
		ActiveTrigger();
		break;
	}
}

#pragma endregion