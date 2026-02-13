// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Base/Anomaly_Base_Neapolitan.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"
#include "Anomaly/Object/Anomaly_Object_Neapolitan.h"

// Anomaly_Base_Neapolitan.cpp

#pragma region Base

AAnomaly_Base_Neapolitan::AAnomaly_Base_Neapolitan(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void AAnomaly_Base_Neapolitan::BeginPlay()
{
	Super::BeginPlay();
	SetVerdictMode(EAnomalyVerdictMode::Both_AND); // VerdictMode Setting
}

#pragma endregion