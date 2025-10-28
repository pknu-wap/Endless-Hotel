// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"

#pragma region Base

AAnomaly_Base_EightExit::AAnomaly_Base_EightExit(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

#pragma region VerdictMode

#pragma endregion


void AAnomaly_Base_EightExit::BeginPlay()
{
	Super::BeginPlay();
    SetVerdictMode(EAnomalyVerdictMode::AnomalyElevatorOnly); // VerdictMode Setting
    bIsActive = true;
}

#pragma endregion

#pragma region Activities

// Anomaly_Base_EightExit.cpp
void AAnomaly_Base_EightExit::ActivateAnomaly_Implementation(uint8 Anomaly_ID)
{
    // Activites
    UE_LOG(LogTemp, Log, TEXT("[EightExit] AnomalyID: %d Activated."), AnomalyID);
}
#pragma endregion