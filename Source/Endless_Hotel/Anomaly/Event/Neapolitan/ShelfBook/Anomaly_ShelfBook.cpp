// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Event/Neapolitan/ShelfBook/Anomaly_ShelfBook.h"
#include "Anomaly/Object/Neapolitan/ShelfBook/Anomaly_Object_ShelfBook.h"

#pragma region Activity

void AAnomaly_ShelfBook::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyID)
	{
	case EAnomalyID::Shelf_Book:
		SetupAnomalyAction<AAnomaly_Object_ShelfBook>(&AAnomaly_Object_ShelfBook::FallSound, FAnomalyActionInfo({ EInteractType::Restore }));
		ActiveTrigger();
		break;
	}
}
#pragma endregion