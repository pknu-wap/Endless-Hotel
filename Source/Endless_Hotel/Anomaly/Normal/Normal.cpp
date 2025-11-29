// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Normal/Normal.h"

#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"

#pragma region Base

ANormal::ANormal(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

void ANormal::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("[EightExit] It's Normal"), AnomalyID);
    SetVerdictMode(EAnomalyVerdictMode::Normal); // VerdictMode Setting
}

#pragma endregion

#pragma region Activities

// Anomaly_Base_EightExit.cpp
void ANormal::ActivateAnomaly(uint8 Anomaly_ID)
{
    // Activites
    UE_LOG(LogTemp, Log, TEXT("[EightExit] It's Normal"), AnomalyID);
}
#pragma endregion