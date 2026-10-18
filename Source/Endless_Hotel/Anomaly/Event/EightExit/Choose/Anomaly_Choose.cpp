// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/Choose/Anomaly_Choose.h"
#include "GameSystem/SubSystem/EHGameSystem.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"

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
	UEHGameSystem* GameSystem = GetGameInstance()->GetSubsystem<UEHGameSystem>();
	if (GameSystem->ChooseKeyIndex == 2)
	{
		SetVerdictMode(EAnomalyVerdictMode::Normal);
	}
}

#pragma endregion