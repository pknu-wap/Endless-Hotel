// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Light/Anomaly_Light.h"
#include "Anomaly/Object/Light/Anomaly_Object_Light.h"

#pragma region Activity

void AAnomaly_Light::ActivateAnomaly_Implementation(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly_Implementation(Anomaly_ID);

	switch (Anomaly_ID)
	{
	case 2:
		AnomalyAction = ([](AAnomaly_Object_Base* AnomalyObject)
			{
				Cast<AAnomaly_Object_Light>(AnomalyObject)->DropLight();
			});
		NextActionDelay = 0.5f;
		break;

	case 3:
		AnomalyAction = ([](AAnomaly_Object_Base* AnomalyObject)
			{
				Cast<AAnomaly_Object_Light>(AnomalyObject)->ChangeLightColor();
			});
		NextActionDelay = 0.5f;
		break;
	}

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &ThisClass::StartAnomalyAction, 20, false);
}

void AAnomaly_Light::StartAnomalyAction()
{
	TWeakObjectPtr<AAnomaly_Light> Wrapper = this;
	FTimerHandle LightHandle;
	GetWorld()->GetTimerManager().SetTimer(LightHandle, [Wrapper, LightHandle]() mutable
		{
			for (auto* FoundActor : Wrapper->LinkedObjects)
			{
				auto* Light = Cast<AAnomaly_Object_Light>(FoundActor);
				if (Wrapper->CurrentIndex == Light->LightIndex)
				{
					Wrapper->AnomalyAction(Light);
				}
			}

			if (++Wrapper->CurrentIndex > Wrapper->MaxIndex)
			{
				Wrapper->GetWorld()->GetTimerManager().ClearTimer(LightHandle);
			}
		}, NextActionDelay, true);
}

#pragma endregion