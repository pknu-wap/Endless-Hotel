// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/Anomaly_Event_EightExit.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"

#pragma region Base

void AAnomaly_Event_EightExit::BeginPlay()
{
	Super::BeginPlay();
    SetVerdictMode(EAnomalyVerdictMode::Both_And); // VerdictMode Setting
}

#pragma endregion