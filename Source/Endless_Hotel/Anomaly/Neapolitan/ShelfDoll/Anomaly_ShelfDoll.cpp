// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Neapolitan/ShelfDoll/Anomaly_ShelfDoll.h"
#include "Anomaly/Object/ShelfDoll/Anomaly_Object_ShelfDoll.h"

void AAnomaly_ShelfDoll::ActivateAnomaly(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly(Anomaly_ID);

	switch (Anomaly_ID)
	{
	case 11:
			AnomalyAction = ([](AAnomaly_Object_Base* Object)
			{
				AAnomaly_Object_ShelfDoll* ShelfDollObj = Cast<AAnomaly_Object_ShelfDoll>(Object);
				if (!ShelfDollObj)
				{
					return;
				}

				ShelfDollObj->ActivateDoll_Show();
				ShelfDollObj->ActivateShelfBook_Hide();
			});
			break;

		default:
			break;
	}

	StartAnomalyAction();
}
