// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/ShelfBook/Anomaly_ShelfBook.h"
#include "Anomaly/Object/ShelfBook/Anomaly_Object_ShelfBook.h"

#pragma region Activitiy

void AAnomaly_ShelfBook::ActivateAnomaly()
{
	Super::ActivateAnomaly();

	switch (AnomalyID)
	{
	case 9:
		AnomalyAction = ([](AAnomaly_Object_Base* AnomlayObject)
			{
				if (auto* ShelfBook = Cast<AAnomaly_Object_ShelfBook>(AnomlayObject))
				{
					ShelfBook->ActiveTrigger();
				}
			});
		break;
	}
	StartAnomalyAction();
}
#pragma endregion
