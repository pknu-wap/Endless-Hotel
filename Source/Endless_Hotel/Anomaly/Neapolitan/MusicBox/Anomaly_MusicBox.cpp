// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Neapolitan/MusicBox/Anomaly_MusicBox.h"
#include "Anomaly/Object/Neapolitan/MusicBox/Anomaly_Object_MusicBox.h"

#pragma region Activity

void AAnomaly_MusicBox::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyName::MusicBox_Ringing:
		SetupAnomalyAction(&AAnomaly_Object_MusicBox::PlayMusicBox, { EInteractType::TurnOff });
		ScheduleAnomaly(10);
		break;
	}
}

#pragma endregion