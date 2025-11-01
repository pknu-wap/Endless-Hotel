// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Light/Anomaly_Light.h"
#include "Anomaly/Object/Light/Anomaly_Object_Light.h"
#include "Kismet/GameplayStatics.h"

#pragma region Activity

void AAnomaly_Light::ActivateAnomaly_Implementation(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly_Implementation(Anomaly_ID);

	switch (Anomaly_ID)
	{
	case 1:
		LightAction = ([](AAnomaly_Object_Light* Light) {Light->DropLight(); });
		NextActionDelay = 0.5f;
		break;

	case 2:
		LightAction = ([](AAnomaly_Object_Light* Light) {Light->ChangeLightColor(); });
		NextActionDelay = 2;
		break;
	}

	StartLightAction();
}

#pragma endregion

#pragma region Light

void AAnomaly_Light::StartLightAction()
{
	FTimerHandle LightHandle;
	GetWorld()->GetTimerManager().SetTimer(LightHandle, [this, LightHandle]() mutable
		{
			for (auto* FoundActor : LinkedObjects)
			{
				auto* Light = Cast<AAnomaly_Object_Light>(FoundActor);
				if (CurrentIndex == Light->LightIndex)
				{
					LightAction(Light);
				}
			}

			if (++CurrentIndex > MaxIndex)
			{
				GetWorld()->GetTimerManager().ClearTimer(LightHandle);
			}
		}, NextActionDelay, true);
}

#pragma endregion