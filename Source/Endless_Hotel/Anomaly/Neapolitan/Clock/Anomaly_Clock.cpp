// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Neapolitan/Clock/Anomaly_Clock.h"
#include "Anomaly/Object/Clock/Anomaly_Object_Clock.h"

#pragma region Activity

void AAnomaly_Clock::ActivateAnomaly()
{
	Super::ActivateAnomaly();

	switch (AnomalyID)
	{
	case 89:
		AnomalyAction = ([](AAnomaly_Object_Base* Clock)
			{
				Cast<AAnomaly_Object_Clock>(Clock)->RingingClock();
			});
		StartDelay(20);
		break;
	}
}

#pragma endregion