// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/Normal/Normal.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include "GameSystem/SubSystem/ElevatorManagerSubsystem.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Player/Character/EHPlayer.h"
#include "Player/Controller/EHPlayerController.h"
#include "Anomaly/Object/EightExit/Door/Anomaly_Object_Door.h"
#include <Kismet/GameplayStatics.h>

#pragma region Activities

void ANormal::SetAnomalyState()
{
    SetVerdictMode(EAnomalyVerdictMode::Normal);
    Super::SetAnomalyState();
    auto* VerdictSubsystem = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();
    auto* FloorSubsystem = GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>();
    auto* ElevatorSubsystem = GetGameInstance()->GetSubsystem<UElevatorManagerSubsystem>();

    auto* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (VerdictSubsystem->bIsStartInBed || FloorSubsystem->bIsFirstStartFloor)
    {
        ElevatorSubsystem->RemoveTargetElevator();
        Player->SetActorTransform(Player->StartTransform);
    }
    if (FloorSubsystem->bIsFirstStartFloor)
    {
        SetupAnomalyAction<AAnomaly_Object_Door>(&AAnomaly_Object_Door::ReadyDoor);
		SetupAnomalyAction<AAnomaly_Object_Door>(&AAnomaly_Object_Door::SetLight, FAnomalyActionInfo(), true);
    }
    else if (FloorSubsystem->Floor == STARTFLOOR)
    {
        SetupAnomalyAction<AAnomaly_Object_Door>(&AAnomaly_Object_Door::ReadyDoorOpened);
        SetupAnomalyAction<AAnomaly_Object_Door>(&AAnomaly_Object_Door::SetLight, FAnomalyActionInfo(), true);
    }
    ScheduleAnomaly();
}

#pragma endregion