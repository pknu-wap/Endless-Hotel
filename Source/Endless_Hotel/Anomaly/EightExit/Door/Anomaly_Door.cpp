// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Door/Anomaly_Door.h"
#include "Anomaly/Object/Door/Anomaly_Object_Door.h"
#include "Kismet/GameplayStatics.h"

#pragma region Activity

void AAnomaly_Door::ActivateAnomaly_Implementation(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly_Implementation(Anomaly_ID);

	switch (Anomaly_ID)
	{
		case 3:
			DoorAction = ([](AAnomaly_Object_Door* Door) {Door->ActiveTrigger(); });
		break;
	}

	StartDoorAction();
}

#pragma endregion

#pragma region Door

void AAnomaly_Door::StartDoorAction()
{
	FTimerHandle DoorHandle;
	GetWorld()->GetTimerManager().SetTimer(DoorHandle, [this]() mutable
		{
			for (auto* FoundActor : LinkedObjects)
			{
				auto* Light = Cast<AAnomaly_Object_Door>(FoundActor);
				DoorAction(Light);
			}
		}, 0.5f, true);
}

#pragma endregion