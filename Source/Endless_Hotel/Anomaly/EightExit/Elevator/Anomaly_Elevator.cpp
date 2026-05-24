// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Elevator/Anomaly_Elevator.h"
#include "Actor/Elevator/Elevator.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include <Kismet/GameplayStatics.h>
#include <EngineUtils.h>

#pragma region Base

void AAnomaly_Elevator::BeginPlay()
{
    Super::BeginPlay();
    
    auto* SubSystem = GetGameInstance()->GetSubsystem<UGameSystem>();
    TargetElevator = SubSystem->GetElevatorByID(TargetAnomalyElevatorID);
}

#pragma endregion

#pragma region Activity

void AAnomaly_Elevator::SetAnomalyState()
{
    switch (AnomalyName)
    {
    case EAnomalyID::ElevatorNoFloor:
        TargetElevator->DisableElevatorFloor();
        ScheduleAnomaly();
        break;
    }
}

#pragma endregion
