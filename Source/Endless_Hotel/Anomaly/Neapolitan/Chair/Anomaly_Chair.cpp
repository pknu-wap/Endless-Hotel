// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Neapolitan/Chair/Anomaly_Chair.h"
#include "Anomaly/Object/Neapolitan/Chair/Anomaly_Object_Chair.h"

#pragma region Activity

void AAnomaly_Chair::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyName::Chair_Moving:
		AnomalyAction = ([](AAnomaly_Object_Base* Chair)
			{
				Cast<AAnomaly_Object_Chair>(Chair)->ChairMoving();
			});
		ScheduleAnomaly(20);
		break;
	}
}

#pragma endregion