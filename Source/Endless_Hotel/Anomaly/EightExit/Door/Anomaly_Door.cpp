// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Door/Anomaly_Door.h"
#include "Anomaly/Object/Door/Anomaly_Object_Door.h"

#pragma region Activity

void AAnomaly_Door::ActivateAnomaly_Implementation(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly_Implementation(Anomaly_ID);

	switch (Anomaly_ID)
	{
		case 4:
			AnomalyAction = ([](AAnomaly_Object_Base* AnomalyObject)
				{
					Cast<AAnomaly_Object_Door>(AnomalyObject)->ActiveTrigger();
				});
		break;
	}

	StartAnomalyAction();
}

#pragma endregion