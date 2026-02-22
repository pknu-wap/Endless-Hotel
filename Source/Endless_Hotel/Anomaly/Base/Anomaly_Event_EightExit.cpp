// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Base/Anomaly_Event_EightExit.h"
#include "GameSystem/SubSystem/GameSystem.h"

#pragma region Base

AAnomaly_Event_EightExit::AAnomaly_Event_EightExit(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

void AAnomaly_Event_EightExit::BeginPlay()
{
	Super::BeginPlay();
    SetVerdictMode(EAnomalyVerdictMode::Both_AND); // VerdictMode Setting
}

#pragma endregion
