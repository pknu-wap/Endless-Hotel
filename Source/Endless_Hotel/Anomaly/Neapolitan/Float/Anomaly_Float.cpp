// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Neapolitan/Float/Anomaly_Float.h"
#include "Anomaly/Object/Float/Anomaly_Object_Float.h"

#pragma region Activity

void AAnomaly_Float::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();

	switch (AnomalyName)
	{
	case EAnomalyName::Float:
		AnomalyAction = ([this](AAnomaly_Object_Base* Float)
			{
				Cast<AAnomaly_Object_Float>(Float)->SearchAndStart();
			});
		ScheduleAnomaly(10);
		break;
	}
}

#pragma endregion