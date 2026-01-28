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
		AnomalyAction = ([](AAnomaly_Object_Base* Float)
			{
				Cast<AAnomaly_Object_Float>(Float)->StartFloating();
				/*Cast<AAnomaly_Object_Float>(Float)->SetInteraction();*/
			});
		ScheduleAnomaly(10);
		break;
	}
}

#pragma endregion