// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/ShelfPlant/Anomaly_ShelfPlant.h"
#include "Anomaly/Object/EightExit/ShelfPlant/Anomaly_Object_ShelfPlant.h"

#pragma region Activity

void AAnomaly_ShelfPlant::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyID)
	{
	case EAnomalyID::Plant_Change:
		SetupAnomalyAction<AAnomaly_Object_ShelfPlant>(&AAnomaly_Object_ShelfPlant::StartChange);
		ScheduleAnomaly();
		break;
	}
}

#pragma endregion