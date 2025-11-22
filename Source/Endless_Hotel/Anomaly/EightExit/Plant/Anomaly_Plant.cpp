// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/Plant/Anomaly_Plant.h"
#include "Anomaly/Object/Plant/Anomaly_Object_Plant.h"

#pragma region Activity

void AAnomaly_Plant::ActivateAnomaly_Implementation(uint8 Anomaly_ID)
{

	switch (Anomaly_ID)
	{
	case 6:
		AnomalyAction = ([](AAnomaly_Object_Base* AnomalyObject)
			{
			});
		break;
	}

}