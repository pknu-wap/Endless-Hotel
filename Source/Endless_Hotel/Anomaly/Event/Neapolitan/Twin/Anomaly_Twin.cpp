// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Event/Neapolitan/Twin/Anomaly_Twin.h"
#include "Anomaly/Object/Neapolitan/Twin/Anomaly_Object_Twin.h"

#pragma region Twin

void AAnomaly_Twin::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyID::Twin:
		SetupAnomalyAction(&AAnomaly_Object_Twin::StartTwin);
		break;
	}
	ActiveTrigger();
}

void AAnomaly_Twin::DisableAnomaly()
{
	AAnomaly_Object_Twin* TwinObject = Cast<AAnomaly_Object_Twin>(TargetAnomalyObjects[0]);
	TwinObject->SetActorLocation(FVector(0, 0, 0));
	Super::DisableAnomaly();
}

#pragma endregion
