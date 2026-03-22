// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/Shelf/Anomaly_Shelf.h"
#include "Anomaly/Object/EightExit/Shelf/Anomaly_Object_Shelf.h"

#pragma region Activity

void AAnomaly_Shelf::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyName::Plant_Change:
		SetupAnomalyAction(&AAnomaly_Object_Shelf::StartChange);
		ScheduleAnomaly();
		break;
	}

	switch (AnomalyName)
	{
	case EAnomalyName::Shelf_Book:
		SetupAnomalyAction(&AAnomaly_Object_Shelf::FallSound);
		ActiveTrigger();
		break;
	}
}
#pragma endregion