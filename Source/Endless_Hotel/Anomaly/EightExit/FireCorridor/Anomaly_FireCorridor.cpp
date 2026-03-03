// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/FireCorridor/Anomaly_FireCorridor.h"

#pragma region Base

AAnomaly_FireCorridor::AAnomaly_FireCorridor(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PlayerStartTransform.SetLocation(FVector(-750.0, 570.0 ,2342.0));
}

#pragma endregion

#pragma region Activity

void AAnomaly_FireCorridor::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyName::FireCorridor:
		ScheduleAnomaly();
		break;
	}
}

#pragma endregion