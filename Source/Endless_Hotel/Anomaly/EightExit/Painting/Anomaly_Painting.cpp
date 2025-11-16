// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Painting/Anomaly_Painting.h"
#include "Anomaly/Object/Painting/Anomaly_Object_Painting.h"

#pragma region Activity

void AAnomaly_Painting::ActivateAnomaly_Implementation(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly_Implementation(Anomaly_ID);

	switch (Anomaly_ID)
	{
	case 10: // 임시 ID 번호
		AnomalyAction = ([](AAnomaly_Object_Base* Portrait)
			{
				Cast<AAnomaly_Object_Painting>(Portrait)->EyeFollowing();
			});
		break;

	case 11: // 임시 ID 번호
		AnomalyAction = ([](AAnomaly_Object_Base* Portrait)
			{
				Cast<AAnomaly_Object_Painting>(Portrait)->BloodDropping();
			});
		break;
	}

	StartAnomalyAction();
}

#pragma endregion