// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/ShelfBook/Anomaly_ShelfBook.h"
#include "Anomaly/Object/ShelfBook/Anomaly_Object_ShelfBook.h"

#pragma region Activity

void AAnomaly_ShelfBook::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();

	switch (AnomalyName)
	{
	case EAnomalyName::Shelf_Book:
		AnomalyAction = ([](AAnomaly_Object_Base* Object)
			{
			});
		ActiveTrigger();
		break;
	}
}
#pragma endregion
