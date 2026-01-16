// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/SignDrop/Anomaly_SignDrop.h"
#include "Anomaly/Object/SignDrop/Anomaly_Object_SignDrop.h"

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

void AAnomaly_SignDrop::ActivateAnomaly()
{
	Super::ActivateAnomaly();

	switch (AnomalyID)
	{
	case 21:
		AnomalyAction = ([](AAnomaly_Object_Base* AnomalyObject)
			{
				Cast<AAnomaly_Object_SignDrop>(AnomalyObject)->ExecuteSignDrop();
			});
		break;
	}
	ActiveTrigger();
}

#pragma endregion
