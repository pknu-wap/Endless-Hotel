// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Hair/Anomaly_Hair.h"
#include "Anomaly/Object/EightExit/Hair/Anomaly_Object_Hair.h"

#pragma region Base

AAnomaly_Hair::AAnomaly_Hair(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

}

void AAnomaly_Hair::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(SpawnLocation);
}

#pragma endregion

#pragma region Activity

void AAnomaly_Hair::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();

	switch (AnomalyName)
	{
	case EAnomalyName::Hair:
		AnomalyAction = ([](AAnomaly_Object_Base* AnomalyObject)
			{
				Cast<AAnomaly_Object_Hair>(AnomalyObject)->StartHair();
			});
		break;
	}
	ActiveTrigger();
}

#pragma endregion

