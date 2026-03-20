// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Neapolitan/SignDrop/Anomaly_SignDrop.h"
#include "Anomaly/Object/Neapolitan/SignDrop/Anomaly_Object_SignDrop.h"

#pragma region Base

AAnomaly_SignDrop::AAnomaly_SignDrop(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void AAnomaly_SignDrop::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(SpawnLocation);
}

#pragma endregion

#pragma region Activity

void AAnomaly_SignDrop::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyName::SignDrop:
		AnomalyAction = MakeAnomalyAction(&AAnomaly_Object_SignDrop::ExecuteSignDrop);
		break;
	}
	ActiveTrigger();
}

#pragma endregion
