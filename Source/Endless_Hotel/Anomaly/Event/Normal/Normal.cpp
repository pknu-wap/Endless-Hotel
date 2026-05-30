// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/Normal/Normal.h"
#include "GameSystem/SubSystem/GameSystem.h"

#pragma region Base

void ANormal::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("[EightExit] It's Normal"), AnomalyName);
    SetVerdictMode(EAnomalyVerdictMode::Normal); // VerdictMode Setting
}

#pragma endregion

#pragma region Activities

// Anomaly_Event_EightExit.cpp
void ANormal::SetAnomalyState()
{
    // Activites
	AnomalyName = EAnomalyID::None;
    UE_LOG(LogTemp, Log, TEXT("[EightExit] It's Normal"), AnomalyName);
}
#pragma endregion