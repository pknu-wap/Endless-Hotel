// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Anomaly_Base/Anomaly_Base_EightExit.h"

#pragma region Base

AAnomaly_Base_EightExit::AAnomaly_Base_EightExit(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    Super::ActivateAnomaly_Implementation();
    VerdictMode = EAnomalyVerdictMode::CorrectElevatorOnly; // VerdictMode Setting
}

#pragma endregion

#pragma region Activities

// Anomaly_Base_EightExit.cpp
void AAnomaly_Base_EightExit::ActivateAnomaly_Implementation()
{
    // Activites
    UE_LOG(LogTemp, Log, TEXT("[EightExit] Activated."));
}
#pragma endregion