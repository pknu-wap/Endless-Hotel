// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Elevator/Anomaly_Elevator.h"
#include "Actor/Elevator/Elevator.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "Player/Character/EHPlayer.h"
#include <Components/BoxComponent.h>
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

void AAnomaly_Elevator::OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AEHPlayer* Player = Cast<AEHPlayer>(OtherActor);
    if (!Player) return;
    Player->DieDelegate.Broadcast(EDeathReason::Fall);
}

void AAnomaly_Elevator::SetAnomalyState()
{
    switch (AnomalyName)
    {
    case EAnomalyID::ElevatorNoFloor:
        TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        TriggerBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnTriggerBox);
        TargetElevator->DisableElevatorFloor();
        ScheduleAnomaly();
        break;
    }
}

#pragma endregion
