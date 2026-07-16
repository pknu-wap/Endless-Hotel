// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/Normal/Normal.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Player/Character/EHPlayer.h"
#include "Anomaly/Object/EightExit/Door/Anomaly_Object_Door.h"
#include <Kismet/GameplayStatics.h>

#pragma region Activities

void ANormal::SetAnomalyState()
{
    SetVerdictMode(EAnomalyVerdictMode::Normal);
    Super::SetAnomalyState();
    auto* Subsystem = GetGameInstance()->GetSubsystem<UGameSystem>();
    auto* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (Subsystem->bIsStartInBed && Subsystem->Floor == STARTFLOOR)
    {
        Subsystem->RemoveTargetElevator();
        Player->SetActorTransform(Player->StartTransform);
        Subsystem->bIsStartInBed = false;
    }
    if (Subsystem->bIsFirstStartFloor)
    {
        SetupAnomalyAction(&AAnomaly_Object_Door::ReadyDoor);
    }
    else if (Subsystem->Floor == STARTFLOOR)
    {
        SetupAnomalyAction(&AAnomaly_Object_Door::ReadyDoorOpened);
    }
    ScheduleAnomaly();
}
#pragma endregion