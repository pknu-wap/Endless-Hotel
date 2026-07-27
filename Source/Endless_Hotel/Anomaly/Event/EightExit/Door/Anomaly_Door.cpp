// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/Door/Anomaly_Door.h"
#include "Anomaly/Object/EightExit/Door/Anomaly_Object_Door.h"
#include <Components/BoxComponent.h>

#pragma region Base

AAnomaly_Door::AAnomaly_Door(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TriggerBox_Close = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox_Close"));
	TriggerBox_Close->SetupAttachment(RootComponent);
	TriggerBox_Close->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

#pragma endregion

#pragma region Activity

void AAnomaly_Door::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyID)
	{
	case EAnomalyID::Door_Shake:
		SetupAnomalyAction<AAnomaly_Object_Door>(&AAnomaly_Object_Door::StartShaking);
		ActiveTrigger();
		break;
	}
}

#pragma endregion