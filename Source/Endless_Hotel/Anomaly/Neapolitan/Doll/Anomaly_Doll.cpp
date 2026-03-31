// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Neapolitan/Doll/Anomaly_Doll.h"
#include "Anomaly/Object/Neapolitan/Doll/Anomaly_Object_Doll.h"
#include <Kismet/GameplayStatics.h>

void AAnomaly_Doll::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyName::Doll:
		SetupAnomalyAction(&AAnomaly_Object_Doll::ActivateDoll_Show);
		ScheduleAnomaly();
		break;
	}
}