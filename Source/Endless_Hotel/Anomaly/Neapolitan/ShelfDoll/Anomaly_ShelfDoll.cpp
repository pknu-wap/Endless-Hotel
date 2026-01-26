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

			TArray<AActor*> Books;
			UGameplayStatics::GetAllActorsOfClass(Object->GetWorld(), AAnomaly_Object_ShelfBook::StaticClass(), Books);
			for (AActor* A : Books)
			{
				if (auto* Book = Cast<AAnomaly_Object_ShelfBook>(Object))
					Book->StartBookOff();
			}
			
			TArray<AActor*> Plants;
			UGameplayStatics::GetAllActorsOfClass(Object->GetWorld(), AAnomaly_Object_Plant::StaticClass(), Plants);
			for (AActor* A : Plants)
			{
				if (auto* Plant = Cast<AAnomaly_Object_Plant>(Object))
					Plant->StartPlantOff();
			}
		});
		ScheduleAnomaly();
		break;
	}
}
