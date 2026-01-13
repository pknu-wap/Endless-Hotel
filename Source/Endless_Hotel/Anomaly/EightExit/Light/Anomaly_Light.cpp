// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Light/Anomaly_Light.h"
#include "Anomaly/Object/Light/Anomaly_Object_Light.h"
#include "Components/BoxComponent.h"

#pragma region Base

AAnomaly_Light::AAnomaly_Light(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

#pragma endregion

#pragma region Activity

void AAnomaly_Light::ActivateAnomaly()
{
	Super::ActivateAnomaly();

	switch (AnomalyID)
	{
	case 2:
		AnomalyAction = ([](AAnomaly_Object_Base* AnomalyObject)
			{
				Cast<AAnomaly_Object_Light>(AnomalyObject)->DropLight();
			});
		break;

	case 3:
		AnomalyAction = ([](AAnomaly_Object_Base* AnomalyObject)
			{
				Cast<AAnomaly_Object_Light>(AnomalyObject)->ChangeLightColor();
			});
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
					AnomalyAction(Light);
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