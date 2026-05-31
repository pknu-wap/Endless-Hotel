// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/Light/Anomaly_Light.h"
#include "Anomaly/Object/EightExit/Light/Anomaly_Object_Light.h"
#include <Components/BoxComponent.h>

#pragma region Activity

void AAnomaly_Light::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyID::Light_Destroy:
		SetupAnomalyAction(&AAnomaly_Object_Light::DropLight);
		ActiveTrigger();
		break;

	case EAnomalyID::Light_Blue:
		SetupAnomalyAction(&AAnomaly_Object_Light::ChangeLightColor);
		ActiveTrigger();
		break;
	}
}

void AAnomaly_Light::StartAnomalyAction()
{
	FTimerHandle LightHandle;
	GetWorld()->GetTimerManager().SetTimer(LightHandle, FTimerDelegate::CreateWeakLambda(this, [this, LightHandle]() mutable
		{
			TArray<AActor*> RemoveTargets;

			for (auto* FoundActor : LinkedObjects)
			{
				auto* Light = Cast<AAnomaly_Object_Light>(FoundActor);
				if (CurrentIndex == Light->LightIndex)
				{
					AnomalyActions[0](Light);
					RemoveTargets.Add(FoundActor);
				}
			}

			for (auto* RemoveTarget : RemoveTargets)
			{
				LinkedObjects.Remove(RemoveTarget);
			}

			if (++CurrentIndex > MaxIndex)
			{
				GetWorld()->GetTimerManager().ClearTimer(LightHandle);
			}
		}), NextActionDelay, true);
}

#pragma endregion