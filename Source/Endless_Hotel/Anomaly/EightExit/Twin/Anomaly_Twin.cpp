// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/Twin/Anomaly_Twin.h"
#include "Anomaly/Object/Neapolitan/Twin/Anomaly_Object_Twin.h"

#pragma region Base

AAnomaly_Twin::AAnomaly_Twin(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void AAnomaly_Twin::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(SpawnLocation);
}

#pragma endregion

#pragma region Twin

void AAnomaly_Twin::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyName::Twin:
		AnomalyAction = ([](AAnomaly_Object_Base* AnomalyObject)
			{
				Cast<AAnomaly_Object_Twin>(AnomalyObject)->TwinReveal();
			});
		break;
	}
	ActiveTrigger();
}

#pragma endregion
