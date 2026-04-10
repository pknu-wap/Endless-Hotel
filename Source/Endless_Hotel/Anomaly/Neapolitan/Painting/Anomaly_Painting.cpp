// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Neapolitan/Painting/Anomaly_Painting.h"
#include "Anomaly/Object/Neapolitan/Painting/Anomaly_Object_Painting.h"

#pragma region Activity

void AAnomaly_Painting::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyName::Painting_Eye:
		SetupAnomalyAction(&AAnomaly_Object_Painting::EyeFollowing, { EInteractType::Rotate });
		ScheduleAnomaly();
		break;
	case EAnomalyName::Painting_Blood:
		SetupAnomalyAction(&AAnomaly_Object_Painting::BloodDropping, { EInteractType::Rotate });
		ActiveTrigger();
		break;
	case EAnomalyName::Painting_Blur:
		SetupAnomalyAction(&AAnomaly_Object_Painting::BlurPaint, { EInteractType::Rotate });
		ScheduleAnomaly();
		break;
	case EAnomalyName::Painting_Tilt:
		SetupAnomalyAction(&AAnomaly_Object_Painting::FrameTilt, { EInteractType::Rotate });
		ScheduleAnomaly(10.0f);
		break;
	}
}

#pragma endregion