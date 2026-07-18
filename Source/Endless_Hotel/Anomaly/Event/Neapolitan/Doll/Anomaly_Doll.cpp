// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/Neapolitan/Doll/Anomaly_Doll.h"
#include "Anomaly/Object/Neapolitan/Doll/Anomaly_Object_Doll.h"

#pragma region Activity

void AAnomaly_Doll::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyID)
	{
	case EAnomalyID::Doll:
		SetupAnomalyAction(&AAnomaly_Object_Doll::ActivateDoll_Show, { EInteractType::Burn });
		ScheduleAnomaly();
		break;

	case EAnomalyID::Doll_Coming:
		SetupAnomalyAction(&AAnomaly_Object_Doll::ActivateDoll_Show);
		SetupAnomalyAction(&AAnomaly_Object_Doll::SpawnComingDolls, { EInteractType::Burn });
		ActiveTrigger();
		break;
	}
}

#pragma endregion