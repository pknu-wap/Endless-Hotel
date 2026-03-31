// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Elevator/Anomaly_Elevator.h"
#include "Actor/Elevator/Elevator.h"
#include <Kismet/GameplayStatics.h>
#include <EngineUtils.h>

#pragma region Base

void AAnomaly_Elevator::BeginPlay()
{
    Super::BeginPlay();
    
    for (TActorIterator<AElevator> Iter(GetWorld()); Iter; ++Iter)
    {
        if (Iter->ElevatorID == TargetAnomalyElevatorID)
        {
            TargetElevator = *Iter;
        }
    }
}

#pragma endregion

#pragma region Activity

void AAnomaly_Elevator::SetAnomalyState()
{
    AnomalyName = static_cast<EAnomalyName>(AnomalyID);
    switch (AnomalyName)
    {
    case EAnomalyName::ElevatorNoFloor:
        TargetElevator->DisableElevatorFloor();
        ScheduleAnomaly();
        break;
    }
}

#pragma endregion
