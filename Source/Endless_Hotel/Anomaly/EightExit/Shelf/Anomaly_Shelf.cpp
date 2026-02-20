// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/Shelf/Anomaly_Shelf.h"
#include "Anomaly/Object/EightExit/Shelf/Anomaly_Object_Shelf.h"

#pragma region Activity

void AAnomaly_Shelf::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();

	switch (AnomalyName)
	{
	case EAnomalyName::Plant_Change:
		AnomalyAction = ([](AAnomaly_Object_Base* Object)
			{
				Cast<AAnomaly_Object_Shelf>(Object)->StartChange();
			});
		ScheduleAnomaly();
		break;
	}

	switch (AnomalyName)
	{
	case EAnomalyName::Shelf_Book:
		AnomalyAction = ([](AAnomaly_Object_Base* Object)
			{
				Cast<AAnomaly_Object_Shelf>(Object)->FallSound();
			});
		ActiveTrigger();
		break;
	}
}
#pragma endregion