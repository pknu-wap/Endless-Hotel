// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Base/Anomaly_Event_Neapolitan.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "Anomaly/Object/Anomaly_Object_Neapolitan.h"

// Anomaly_Event_Neapolitan.cpp

#pragma region Base

AAnomaly_Event_Neapolitan::AAnomaly_Event_Neapolitan(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void AAnomaly_Event_Neapolitan::BeginPlay()
{
	Super::BeginPlay();
	SetVerdictMode(EAnomalyVerdictMode::Both_AND); // VerdictMode Setting
}

#pragma endregion