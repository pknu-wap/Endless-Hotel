// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Neapolitan/Twin/Anomaly_Twin.h"
#include "Anomaly/Object/Neapolitan/Twin/Anomaly_Object_Twin.h"

#pragma region Base

AAnomaly_Twin::AAnomaly_Twin(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void AAnomaly_Twin::BeginPlay()
{
	Super::BeginPlay();
}

#pragma endregion

#pragma region Twin

void AAnomaly_Twin::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyName::Twin:
		break;
	}
	//ActiveTrigger();
}

#pragma endregion
