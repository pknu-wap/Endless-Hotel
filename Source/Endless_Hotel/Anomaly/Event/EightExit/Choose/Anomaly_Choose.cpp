// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/Choose/Anomaly_Choose.h"
#include "GameSystem/SubSystem/GameSystem.h"

#pragma region Activity

void AAnomaly_Choose::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyID)
	{
	case EAnomalyID::Choose:
		SetupAnomalyAction(&ThisClass::SetChooseVerdictMode);
		ScheduleAnomaly();
		break;
	}
}

#pragma endregion

#pragma region Verdict

void AAnomaly_Choose::SetChooseVerdictMode()
{
	UGameSystem* GameSystem = GetGameInstance()->GetSubsystem<UGameSystem>();
	if (GameSystem->ChooseKeyIndex == 2)
	{
		SetVerdictMode(EAnomalyVerdictMode::Normal);
	}
}

#pragma endregion