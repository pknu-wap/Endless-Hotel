// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Neapolitan/Painting/Anomaly_Painting.h"
#include "Anomaly/Object/Painting/Anomaly_Object_Painting.h"

#pragma region Activity

void AAnomaly_Painting::ActivateAnomaly(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly(Anomaly_ID);

	switch (Anomaly_ID)
	{
	case 99:
		AnomalyAction = ([](AAnomaly_Object_Base* Portrait)
			{
				Cast<AAnomaly_Object_Painting>(Portrait)->EyeFollowing();
				Cast<AAnomaly_Object_Painting>(Portrait)->ActivateInteraction();
			});
		ActiveTrigger();
		break;

	case 96:
		AnomalyAction = ([](AAnomaly_Object_Base* Portrait)
			{
				Cast<AAnomaly_Object_Painting>(Portrait)->BloodDropping();
				Cast<AAnomaly_Object_Painting>(Portrait)->ActivateInteraction();
			});
		ActiveTrigger();
		break;

	case 95:
		AnomalyAction = ([](AAnomaly_Object_Base* Portrait)
			{
				Cast<AAnomaly_Object_Painting>(Portrait)->BlurPaint();
				Cast<AAnomaly_Object_Painting>(Portrait)->ActivateInteraction();
			});
		StartImmediate();
		break;
	}
}

#pragma endregion