// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Neapolitan/ShelfDoll/Anomaly_ShelfDoll.h"
#include "Anomaly/Object/Neapolitan/ShelfDoll/Anomaly_Object_ShelfDoll.h"
#include <Kismet/GameplayStatics.h>

void AAnomaly_ShelfDoll::SetAnomalyState()
{
	Super::SetAnomalyState();

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
			});
		ScheduleAnomaly();
		break;
	}
}