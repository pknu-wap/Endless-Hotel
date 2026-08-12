// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/Neapolitan/SignDrop/Anomaly_SignDrop.h"
#include "Anomaly/Object/Neapolitan/SignDrop/Anomaly_Object_SignDrop.h"

#pragma region Activity

void AAnomaly_SignDrop::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyID)
	{
	case EAnomalyID::SignDrop:
		SetupAnomalyAction<AAnomaly_Object_SignDrop>(&AAnomaly_Object_SignDrop::ExecuteSignDrop, FAnomalyActionInfo({ EInteractType::Restore }));
		break;
	}

	ActiveTrigger();
}

#pragma endregion