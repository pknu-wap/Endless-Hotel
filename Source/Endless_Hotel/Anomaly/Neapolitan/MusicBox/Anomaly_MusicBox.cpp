// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Neapolitan/MusicBox/Anomaly_MusicBox.h"
#include "Anomaly/Object/MusicBox/Anomaly_Object_MusicBox.h"

#pragma region Activity

void AAnomaly_MusicBox::ActivateAnomaly()
{
	Super::ActivateAnomaly();

	switch (AnomalyID)
	{
	case 90:
		AnomalyAction = ([](AAnomaly_Object_Base* MusicBox)
			{
				Cast<AAnomaly_Object_MusicBox>(MusicBox)->PlayMusicBox();
				Cast<AAnomaly_Object_MusicBox>(MusicBox)->SetInteraction();
			});
		StartImmediate();
		break;
	}
}

#pragma endregion