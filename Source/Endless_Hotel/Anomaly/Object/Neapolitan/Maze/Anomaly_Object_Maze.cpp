// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Maze/Anomaly_Object_Maze.h"
#include "Actor/Elevator/Elevator.h"

#pragma region Base

AAnomaly_Object_Maze::AAnomaly_Object_Maze(const FObjectInitializer& ObjectInitializer)
{
	ElevatorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("ElevatorComponent"));
	ElevatorComponent->SetupAttachment(RootComponent);
	ElevatorComponent->SetChildActorClass(AElevator::StaticClass());

    for (int32 i = 1; i <= 3; ++i)
    {
        FName CompName = FName(*FString::Printf(TEXT("WallComponent_%d"), i));
        UChildActorComponent* WallComp = CreateDefaultSubobject<UChildActorComponent>(CompName);
        WallComp->SetupAttachment(RootComponent);
        WallComponents.Add(WallComp);
    }
}

#pragma endregion


#pragma region MazeMonster

void AAnomaly_Object_Maze::StartMazeMonster()
{
	RandomizeElevatorLocation();
}

#pragma endregion

#pragma region Elevator

void AAnomaly_Object_Maze::RandomizeElevatorLocation()
{
	const uint8 MaxIndex = ElevatorPoint.Num() - 1;
	const uint8 PositionIndex = FMath::RandRange(0, MaxIndex);
	AElevator* TargetElevator = Cast<AElevator>(ElevatorComponent->GetChildActor());

	TargetElevator->SetActorRotation(ElevatorPoint[PositionIndex].Rotation);
	TargetElevator->MapPos = ElevatorPoint[PositionIndex].Location;
	TargetElevator->EndPos = ElevatorPoint[PositionIndex].Location;

	WallComponents[PositionIndex]->GetChildActor()->SetActorHiddenInGame(false);
	WallComponents[PositionIndex]->GetChildActor()->SetActorEnableCollision(false);
}

#pragma endregion
