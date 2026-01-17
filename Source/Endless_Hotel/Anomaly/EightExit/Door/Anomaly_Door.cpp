// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Door/Anomaly_Door.h"
#include "Anomaly/Object/Door/Anomaly_Object_Door.h"
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>

#pragma region Activity

void AAnomaly_Door::ActivateAnomaly()
{
	Super::ActivateAnomaly();

	switch (AnomalyName)
	{
	case EAnomalyName::Door_Shake:
		AnomalyAction = ([this](AAnomaly_Object_Base* AnomalyObject)
			{
				DoorShake();
			});
		ActiveTrigger();
		break;

	case EAnomalyName::Door_Close:
		AnomalyAction = ([](AAnomaly_Object_Base* AnomalyObject)
			{
				Cast<AAnomaly_Object_Door>(AnomalyObject)->ActivateDoorAnomaly();
			});
		ActiveTrigger();
		break;
	}
}

#pragma endregion

#pragma region Shake

void AAnomaly_Door::DoorShake()
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