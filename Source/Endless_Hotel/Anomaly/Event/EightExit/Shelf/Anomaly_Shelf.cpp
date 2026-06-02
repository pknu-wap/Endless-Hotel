// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Event/EightExit/Shelf/Anomaly_Shelf.h"
#include "Anomaly/Object/EightExit/Shelf/Anomaly_Object_Shelf.h"

#pragma region Activity

void AAnomaly_Shelf::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyID::Plant_Change:
		SetupAnomalyAction(&AAnomaly_Object_Shelf::StartChange);
		ScheduleAnomaly();
		break;
	}
}
#pragma endregion