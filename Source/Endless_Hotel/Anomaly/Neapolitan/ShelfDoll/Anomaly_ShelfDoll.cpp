// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Neapolitan/ShelfDoll/Anomaly_ShelfDoll.h"
#include "Anomaly/Object/ShelfDoll/Anomaly_Object_ShelfDoll.h"
#include "Anomaly/Object/ShelfBook/Anomaly_Object_ShelfBook.h"
#include "Anomaly/Object/Plant/Anomaly_Object_Plant.h"
#include <Kismet/GameplayStatics.h>

void AAnomaly_ShelfDoll::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();

	switch (AnomalyName)
	{
	case EAnomalyName::Shelf_Doll:
		AnomalyAction = ([](AAnomaly_Object_Base* Object)
		{
			if (auto* Doll = Cast<AAnomaly_Object_ShelfDoll>(Object))
			{
				Doll->ActivateDoll_Show();
				Doll->SetInteraction();
			}

				ShelfDollObj->ActivateDoll_Show();
				ShelfDollObj->ActivateShelfBook_Hide();
				ShelfDollObj->ActivatePlant_Hide();
				//Cast<AAnomaly_Object_ShelfDoll>(Object)->SetInteraction();
			});
			break;

		default:
			break;
	}
}
