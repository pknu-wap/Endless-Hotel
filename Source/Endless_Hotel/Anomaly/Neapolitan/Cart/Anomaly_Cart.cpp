// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Neapolitan/Cart/Anomaly_Cart.h"
#include "Anomaly/Object/Neapolitan/Cart/Anomaly_Object_Cart.h"

#pragma region Activity

void AAnomaly_Cart::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyName::Cart_Moving:
		SetupAnomalyAction(&AAnomaly_Object_Cart::CartMoving, { EInteractType::Restore });
		ScheduleAnomaly(20);
		break;
	}
}

#pragma endregion