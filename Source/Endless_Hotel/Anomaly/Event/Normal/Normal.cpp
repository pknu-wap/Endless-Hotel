// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/Normal/Normal.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "Anomaly/Object/EightExit/Door/Anomaly_Object_Door.h"

#pragma region Activities

void ANormal::SetAnomalyState()
{
    SetVerdictMode(EAnomalyVerdictMode::Normal);
    Super::SetAnomalyState();
    auto* Subsystem = GetGameInstance()->GetSubsystem<UGameSystem>();
    if (Subsystem->bIsStartInBed || Subsystem->bIsFirstStartFloor)
    {
        Subsystem->RemoveTargetElevator();
    }
    if (Subsystem->bIsFirstStartFloor)
    {
        SetupAnomalyAction<AAnomaly_Object_Door>(&AAnomaly_Object_Door::ReadyDoor);
        SetupAnomalyAction<AAnomaly_Object_Door>(&AAnomaly_Object_Door::SetLight, FAnomalyActionInfo(),true);
    }
    else if (Subsystem->Floor == STARTFLOOR)
    {
        SetupAnomalyAction<AAnomaly_Object_Door>(&AAnomaly_Object_Door::ReadyDoorOpened);
        SetupAnomalyAction<AAnomaly_Object_Door>(&AAnomaly_Object_Door::SetLight, FAnomalyActionInfo(), true);
    }
    ScheduleAnomaly();
}

#pragma endregion