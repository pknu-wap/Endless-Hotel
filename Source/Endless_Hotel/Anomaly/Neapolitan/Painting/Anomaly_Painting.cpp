// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Neapolitan/Painting/Anomaly_Painting.h"
#include "Anomaly/Object/Painting/Anomaly_Object_Painting.h"

#pragma region Activity

void AAnomaly_Painting::ActivateAnomaly(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly(Anomaly_ID);

	switch (Anomaly_ID)
	{
	case 24:
		AnomalyAction = ([](AAnomaly_Object_Base* Portrait)
			{
				Cast<AAnomaly_Object_Painting>(Portrait)->CurrentAnomalyID = 24;
				Cast<AAnomaly_Object_Painting>(Portrait)->ActiveTrigger();
			});
		break;

	case 27:
		AnomalyAction = ([](AAnomaly_Object_Base* Portrait)
			{
				Cast<AAnomaly_Object_Painting>(Portrait)->CurrentAnomalyID = 27;
				Cast<AAnomaly_Object_Painting>(Portrait)->ActiveTrigger();
			});
		break;

	case 31:
		AnomalyAction = ([](AAnomaly_Object_Base* Portrait)
			{
				Cast<AAnomaly_Object_Painting>(Portrait)->CurrentAnomalyID = 31;
				Cast<AAnomaly_Object_Painting>(Portrait)->ActiveTrigger();
			});
		break;
	}
	StartAnomalyAction();
}

#pragma endregion