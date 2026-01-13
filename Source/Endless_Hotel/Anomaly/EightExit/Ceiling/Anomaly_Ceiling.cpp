// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Ceiling/Anomaly_Ceiling.h"
#include "Anomaly/Object/Ceiling/Anomaly_Object_Ceiling.h"

#pragma region Activity

void AAnomaly_Ceiling::ActivateAnomaly()
{
	Super::ActivateAnomaly();

	switch (AnomalyID)
	{
	case 11:
		AnomalyAction = ([](AAnomaly_Object_Base* AnomalyObject)
			{
				Cast<AAnomaly_Object_Ceiling>(AnomalyObject)->PlayCeilingRotate();
			});
		StartDelay(2.0f);
		break;

	case 17:
		AnomalyAction = ([](AAnomaly_Object_Base* AnomalyObject)
			{
				Cast<AAnomaly_Object_Ceiling>(AnomalyObject)->CeilingBloodDripping();
			});
		StartDelay(5.0f);
		break;
	}
	
}

#pragma endregion