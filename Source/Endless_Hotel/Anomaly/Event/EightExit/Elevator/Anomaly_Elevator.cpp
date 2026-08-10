// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/Elevator/Anomaly_Elevator.h"
#include "Actor/Elevator/Elevator.h"
#include "Character/AI/ElevatorGhost/ElevatorGhost.h"
#include "Character/AI/ElevatorGhost/ElevatorGhostController.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "Player/Character/EHPlayer.h"
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include <EngineUtils.h>

#pragma region Activity

void AAnomaly_Elevator::OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AEHPlayer* Player = Cast<AEHPlayer>(OtherActor);
    if (!Player) return;
    Player->OnDie.Broadcast(EDeathReason::Fall);
}

void AAnomaly_Elevator::SetAnomalyState()
{
    AnomalyActions.Empty();
    auto* SubSystem = GetGameInstance()->GetSubsystem<UGameSystem>();
    switch (AnomalyID)
    {
    case EAnomalyID::ElevatorNoFloor:
    {
        TargetElevator = SubSystem->GetElevatorByID(TargetAnomalyElevatorID[0]);
        TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        TriggerBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnTriggerBox);
        this->TargetAnomalyObjects.Add(TargetElevator.Get());
        SetupAnomalyAction<AElevator>(&AElevator::DisableElevatorFloor);
        ScheduleAnomaly();
        break;
    }
    case EAnomalyID::ElevatorGhost:
    {
        TargetElevator = SubSystem->GetElevatorByID(TargetAnomalyElevatorID[1]);
        ElevatorGhost = GetWorld()->SpawnActor<AElevatorGhost>(ElevatorGhostClass, StartTransform);
        auto* ElevatorGhostController = Cast<AElevatorGhostController>(ElevatorGhost->GetController());
        ElevatorGhostController->TargetElevator = TargetElevator;
        ScheduleAnomaly();
        break;
    }
    }
}

void AAnomaly_Elevator::DisableAnomaly()
{
    switch (AnomalyID)
    {
    case EAnomalyID::ElevatorGhost:
        ElevatorGhost->Destroy();
        break;
    }
    Super::DisableAnomaly();
}

#pragma endregion