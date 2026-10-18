// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/Neapolitan/Anomaly_Event_Neapolitan.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"

// Anomaly_Event_Neapolitan.cpp

#pragma region Base

AAnomaly_Event_Neapolitan::AAnomaly_Event_Neapolitan(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
	bIsNeapolitan = true;
}

void AAnomaly_Event_Neapolitan::BeginPlay()
{
	Super::BeginPlay();
	SetVerdictMode(EAnomalyVerdictMode::Both_And); // VerdictMode Setting
}

#pragma endregion