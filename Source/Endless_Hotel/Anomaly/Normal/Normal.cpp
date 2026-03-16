// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Normal/Normal.h"
#include "GameSystem/SubSystem/GameSystem.h"

#pragma region Base

void ANormal::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("[EightExit] It's Normal"), AnomalyID);
    SetVerdictMode(EAnomalyVerdictMode::Normal); // VerdictMode Setting 
}

#pragma endregion

#pragma region Activities

// Anomaly_Event_EightExit.cpp
void ANormal::SetAnomalyState()
{
    // Activites
	AnomalyID = 0;
    UE_LOG(LogTemp, Log, TEXT("[EightExit] It's Normal"), AnomalyID);
}
#pragma endregion