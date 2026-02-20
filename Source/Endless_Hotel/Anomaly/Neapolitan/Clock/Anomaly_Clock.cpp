// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Neapolitan/Clock/Anomaly_Clock.h"
#include "Anomaly/Object/Neapolitan/Clock/Anomaly_Object_Clock.h"

#pragma region Activity

void AAnomaly_Clock::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();

	switch (AnomalyName)
	{
	case EAnomalyName::Clock_Ringing:
		AnomalyAction = ([](AAnomaly_Object_Base* Clock)
			{
				Cast<AAnomaly_Object_Clock>(Clock)->RingingClock();
			});
		ScheduleAnomaly(20);
		break;
	}
}

#pragma endregion