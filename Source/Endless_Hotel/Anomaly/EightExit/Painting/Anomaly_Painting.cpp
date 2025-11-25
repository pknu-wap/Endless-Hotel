// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Painting/Anomaly_Painting.h"
#include "Anomaly/Object/Painting/Anomaly_Object_Painting.h"

#pragma region Activity

void AAnomaly_Painting::ActivateAnomaly_Implementation(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly_Implementation(Anomaly_ID);

	switch (Anomaly_ID)
	{
	case 24:
		AnomalyAction = ([](AAnomaly_Object_Base* Portrait)
			{
				Cast<AAnomaly_Object_Painting>(Portrait)->EyeFollowing();
			});
		break;

	case 27:
		AnomalyAction = ([](AAnomaly_Object_Base* Portrait)
			{
				Cast<AAnomaly_Object_Painting>(Portrait)->BloodDropping();
			});
		break;

	case 31:
		AnomalyAction = ([](AAnomaly_Object_Base* Portrait)
			{
				Cast<AAnomaly_Object_Painting>(Portrait)->BlurPaint();
			});
		break;
	}

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			StartAnomalyAction();
		}), 20, false);
}

#pragma endregion