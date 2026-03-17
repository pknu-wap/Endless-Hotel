// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Neapolitan/MusicBox/Anomaly_MusicBox.h"
#include "Anomaly/Object/Neapolitan/MusicBox/Anomaly_Object_MusicBox.h"

#pragma region Activity

void AAnomaly_MusicBox::SetAnomalyState()
{
	Super::SetAnomalyState();

	AnomalyAction = ([this](AAnomaly_Object_Base* MusicBox)
		{
			auto* MusicBoxObject = Cast<AAnomaly_Object_MusicBox>(MusicBox);
			MusicBoxObject->CorrectInteractType = EInteractType::TurnOff;

			switch (AnomalyName)
			{
			case EAnomalyName::MusicBox_Ringing:
				MusicBoxObject->PlayMusicBox();
				ScheduleAnomaly(10);
				break;
			}
		});
}

#pragma endregion