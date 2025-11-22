// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Ceiling/Anomaly_Ceiling.h"
#include "Anomaly/Object/Ceiling/Anomaly_Object_Ceiling.h"

#pragma region Activity

void AAnomaly_Ceiling::ActivateAnomaly_Implementation(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly_Implementation(Anomaly_ID);

	switch (Anomaly_ID)
	{
	case 11:
		AnomalyAction = ([](AAnomaly_Object_Base* AnomalyObject)
			{
				Cast<AAnomaly_Object_Ceiling>(AnomalyObject)->PlayCeilingRotate();
			});
		break;
	}

	StartAnomalyAction();
}

#pragma endregion