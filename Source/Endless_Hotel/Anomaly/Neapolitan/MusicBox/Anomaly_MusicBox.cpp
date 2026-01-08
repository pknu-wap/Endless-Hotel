// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Neapolitan/MusicBox/Anomaly_MusicBox.h"
#include "Anomaly/Object/MusicBox/Anomaly_Object_MusicBox.h"

#pragma region Activity

void AAnomaly_MusicBox::ActivateAnomaly(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly(Anomaly_ID);

	switch (Anomaly_ID)
	{
	case 90:
		AnomalyAction = ([](AAnomaly_Object_Base* MusicBox)
			{
				Cast<AAnomaly_Object_MusicBox>(MusicBox)->PlayMusicBox();
			});
		StartImmediate();
		break;
	}
}

#pragma endregion