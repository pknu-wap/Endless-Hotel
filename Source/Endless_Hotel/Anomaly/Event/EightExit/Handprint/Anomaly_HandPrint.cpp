// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/HandPrint/Anomaly_HandPrint.h"
#include "Anomaly/Object/EightExit/HandPrint/Anomaly_Object_HandPrint.h"
#include <Components/BoxComponent.h>

#pragma region Activity

void AAnomaly_HandPrint::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyID::Handprint:
		SetupAnomalyAction(&AAnomaly_Object_HandPrint::ReserveCongCong);
		ActiveTrigger();
		break;
	}
}

#pragma endregion