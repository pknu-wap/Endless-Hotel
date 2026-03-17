// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Neapolitan/Painting/Anomaly_Painting.h"
#include "Anomaly/Object/Neapolitan/Painting/Anomaly_Object_Painting.h"

#pragma region Activity

void AAnomaly_Painting::SetAnomalyState()
{
	Super::SetAnomalyState();

	AnomalyAction = ([this](AAnomaly_Object_Base* Portrait)
		{
			auto* PortraitObject = Cast<AAnomaly_Object_Painting>(Portrait);
			PortraitObject->CorrectInteractType = EInteractType::Rotate;

			switch (AnomalyName)
			{
			case EAnomalyName::Painting_Eye:
				PortraitObject->EyeFollowing();
				ActiveTrigger();
				break;
			case EAnomalyName::Painting_Blood:
				PortraitObject->BloodDropping();
				ActiveTrigger();
				break;

			case EAnomalyName::Painting_Blur:
				PortraitObject->BlurPaint();
				ScheduleAnomaly();
				break;

			case EAnomalyName::Painting_Tilt:
				PortraitObject->FrameTilt();
				ScheduleAnomaly(10.0f);
				break;
			}
		});
}

#pragma endregion