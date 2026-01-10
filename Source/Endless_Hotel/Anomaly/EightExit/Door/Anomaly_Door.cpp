// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Door/Anomaly_Door.h"
#include "Anomaly/Object/Door/Anomaly_Object_Door.h"
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>

#pragma region Base

AAnomaly_Door::AAnomaly_Door(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}
#pragma endregion

#pragma region Activity

void AAnomaly_Door::ActivateAnomaly(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly(Anomaly_ID);

	switch (Anomaly_ID)
	{
		case 4:
			AnomalyAction = ([](AAnomaly_Object_Base* AnomalyObject)
				{
					Cast<AAnomaly_Object_Door>(AnomalyObject)->PlayShake_Handle();
				});
		break;

		case 16:
			AnomalyAction = ([](AAnomaly_Object_Base* AnomalyObject)
				{
					Cast<AAnomaly_Object_Door>(AnomalyObject)->StartDoorClose();
				});
			break;
	}
}

void AAnomaly_Door::StartAnomalyAction()
{
	FTimerHandle DoorHandle;
	GetWorld()->GetTimerManager().SetTimer(DoorHandle, FTimerDelegate::CreateWeakLambda(this, [this, DoorHandle]() mutable
		{
			TArray<AActor*> RemoveTargets;

			for (auto* FoundActor : LinkedObjects)
			{
				auto* Door = Cast<AAnomaly_Object_Door>(FoundActor);
				if (CurrentIndex == Door->DoorIndex)
				{
					AnomalyAction(Door);
					RemoveTargets.Add(FoundActor);
				}
			}

			for (auto* RemoveTarget : RemoveTargets)
			{
				LinkedObjects.Remove(RemoveTarget);
			}

			if (++CurrentIndex > MaxIndex)
			{
				GetWorld()->GetTimerManager().ClearTimer(DoorHandle);
			}
		}), NextActionDelay, true);
}

#pragma endregion