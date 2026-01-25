// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/Disappear/Anomaly_Disappear.h"
#include "Anomaly/Object/Disappear/Anomaly_Object_Disappear.h"


#pragma region Activity

void AAnomaly_Disappear::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();

	switch (AnomalyName)
	{
	case EAnomalyName::Disappear:
		AnomalyAction = ([](AAnomaly_Object_Base* Object)
			{
				Cast<AAnomaly_Object_Disappear>(Object)->StartDisappear();
			});
		ScheduleAnomaly();
		break;
	}
}

#pragma endregion