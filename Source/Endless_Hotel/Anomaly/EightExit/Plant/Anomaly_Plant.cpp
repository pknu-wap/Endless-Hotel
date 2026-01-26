// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/Plant/Anomaly_Plant.h"
#include "Anomaly/Object/Plant/Anomaly_Object_Plant.h"
#include "Kismet/GameplayStatics.h"

#pragma region Activity

void AAnomaly_Plant::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();

	switch (AnomalyName)
	{
	case EAnomalyName::Plant_Change:
		AnomalyAction = ([](AAnomaly_Object_Base* Object)S
			{
				Cast<AAnomaly_Object_Plant>(Object)->StartChange();
			});
		ScheduleAnomaly();
		break;
	}
}
#pragma endregion