// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Anomaly_Base/Anomaly_Base_Neapolitan.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"

// Anomaly_Base_Neapolitan.cpp

//AAnomaly_Base_Neapolitan::AAnomaly_Base_Neapolitan(const FObjectInitializer& ObjectInitializer)
//    : Super(ObjectInitializer)
//{
//    Super::ActivateAnomaly_Implementation();
//    VerdictMode = EAnomalyVerdictMode::Both_AND; // VerdictMode Setting
//}

void AAnomaly_Base_Neapolitan::BeginPlay()
{
	Super::BeginPlay();
	SetVerdictMode(EAnomalyVerdictMode::Both_AND); // VerdictMode Setting
}

void AAnomaly_Base_Neapolitan::ActivateAnomaly_Implementation()
{
    // Activites
    UE_LOG(LogTemp, Log, TEXT("[Neapolitan] Activated."));
}
