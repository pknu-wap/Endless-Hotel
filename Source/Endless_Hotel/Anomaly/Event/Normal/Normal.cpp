// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/Normal/Normal.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include "GameSystem/SubSystem/ElevatorManagerSubsystem.h"

#pragma region Activities

void ANormal::SetAnomalyState()
{
    SetVerdictMode(EAnomalyVerdictMode::Normal);
    Super::SetAnomalyState();
    auto* VerdictSubsystem = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();
    auto* FloorSubsystem = GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>();
    auto* ElevatorSubsystem = GetGameInstance()->GetSubsystem<UElevatorManagerSubsystem>();

    if (VerdictSubsystem->bIsStartInBed || FloorSubsystem->bIsFirstStartFloor)
    {
        ElevatorSubsystem->RemoveTargetElevator();
    }
    ScheduleAnomaly();
}

#pragma endregion