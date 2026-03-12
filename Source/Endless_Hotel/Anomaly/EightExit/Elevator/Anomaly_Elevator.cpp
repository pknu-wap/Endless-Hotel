// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Elevator/Anomaly_Elevator.h"
#include "Actor/Elevator/Elevator.h"
#include <Kismet/GameplayStatics.h>

#pragma region Base

void AAnomaly_Elevator::BeginPlay()
{
    Super::BeginPlay();

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AElevator::StaticClass(), FName("TargetElevator"), FoundActors);

    if (FoundActors.Num() > 0)
    {
        TargetElevator = Cast<AElevator>(FoundActors[0]);
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
        TargetElevator->DisableFloor();
        ScheduleAnomaly();
        break;
    }
}

#pragma endregion
