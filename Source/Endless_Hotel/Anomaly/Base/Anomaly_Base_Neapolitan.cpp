// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Base/Anomaly_Base_Neapolitan.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"

// Anomaly_Base_Neapolitan.cpp

AAnomaly_Base_Neapolitan::AAnomaly_Base_Neapolitan(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void AAnomaly_Base_Neapolitan::BeginPlay()
{
	Super::BeginPlay();
	SetVerdictMode(EAnomalyVerdictMode::Both_AND); // VerdictMode Setting
	bIsActive = true;
}

void AAnomaly_Base_Neapolitan::ActivateAnomaly_Implementation(uint8 Anomaly_ID)
{
    // Activites
    UE_LOG(LogTemp, Log, TEXT("[Neapolitan] Activated."));
}
