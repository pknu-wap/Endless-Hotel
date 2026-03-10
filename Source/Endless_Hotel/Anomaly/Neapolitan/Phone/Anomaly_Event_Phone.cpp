// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Neapolitan/Phone/Anomaly_Event_Phone.h"
#include "Anomaly/Object/Neapolitan/Phone/Anomaly_Object_Phone.h"

#pragma region Activity

void AAnomaly_Event_Phone::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyName::Phone_Ringing:
		AnomalyAction = ([](AAnomaly_Object_Base* Phone)
			{
				Cast<AAnomaly_Object_Phone>(Phone)->RingingPhone();
			});
		ScheduleAnomaly(30);
		break;
	}
}

#pragma endregion