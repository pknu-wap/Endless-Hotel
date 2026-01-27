// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Neapolitan/Painting/Anomaly_Painting.h"
#include "Anomaly/Object/Painting/Anomaly_Object_Painting.h"

#pragma region Activity

void AAnomaly_Painting::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();

	switch (AnomalyName)
	{
	case EAnomalyName::Painting_Eye:
		AnomalyAction = ([](AAnomaly_Object_Base* Portrait)
			{
				Cast<AAnomaly_Object_Painting>(Portrait)->EyeFollowing();
				//Cast<AAnomaly_Object_Painting>(Portrait)->SetInteraction();
			});
		ActiveTrigger();
		break;

	case EAnomalyName::Painting_Blood:
		AnomalyAction = ([](AAnomaly_Object_Base* Portrait)
			{
				Cast<AAnomaly_Object_Painting>(Portrait)->BloodDropping();
				//Cast<AAnomaly_Object_Painting>(Portrait)->SetInteraction();
			});
		ActiveTrigger();
		break;

	case EAnomalyName::Painting_Blur:
		AnomalyAction = ([](AAnomaly_Object_Base* Portrait)
			{
				Cast<AAnomaly_Object_Painting>(Portrait)->BlurPaint();
				//Cast<AAnomaly_Object_Painting>(Portrait)->SetInteraction();
			});
		ScheduleAnomaly(0.01f);
		break;

	case EAnomalyName::Painting_Tilt:
		AnomalyAction = ([](AAnomaly_Object_Base* Portrait)
			{
				Cast<AAnomaly_Object_Painting>(Portrait)->FrameTilt();
				//Cast<AAnomaly_Object_Painting>(Portrait)->SetInteraction();
			});
		ScheduleAnomaly(10.0f);
		break;
	}
}

#pragma endregion