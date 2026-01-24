// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Ceiling/Anomaly_Ceiling.h"
#include "Anomaly/Object/Ceiling/Anomaly_Object_Ceiling.h"

#pragma region Activity

void AAnomaly_Ceiling::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();

	switch (AnomalyName)
	{
	case EAnomalyName::Ceil_Rotate:
		AnomalyAction = ([](AAnomaly_Object_Base* AnomalyObject)
			{
				Cast<AAnomaly_Object_Ceiling>(AnomalyObject)->PlayCeilingRotate();
			});
		ScheduleAnomaly(10.0f);
		break;

	case EAnomalyName::Ceil_Blood:
		AnomalyAction = ([](AAnomaly_Object_Base* AnomalyObject)
			{
				Cast<AAnomaly_Object_Ceiling>(AnomalyObject)->CeilingBloodDripping();
			});
		ScheduleAnomaly(10.0f);
		break;
	}
	
}

#pragma endregion