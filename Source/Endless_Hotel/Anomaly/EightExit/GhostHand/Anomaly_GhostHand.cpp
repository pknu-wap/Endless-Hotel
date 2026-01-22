// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/GhostHand/Anomaly_GhostHand.h"
#include "Anomaly/Object/GhostHand/Anomaly_Object_GhostHand.h"

#pragma region Activity

void AAnomaly_GhostHand::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();
	
	switch (AnomalyID)
	{
		case 24:
			AnomalyAction = ([](AAnomaly_Object_Base* AnomalyObject)
				{
					Cast<AAnomaly_Object_GhostHand>(AnomalyObject)->AttachGhostHand();
				});
			ScheduleAnomaly(0.01f);
			break;
	}
}
#pragma endregion