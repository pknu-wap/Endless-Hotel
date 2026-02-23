// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Maze/Anomaly_Object_Maze.h"
#include "Actor/Elevator/Elevator.h"

#pragma region MazeMonster

void AAnomaly_Object_Maze::StartMazeMonster()
{
	SetElevatorPos();
}

#pragma endregion

#pragma region Elevator

void AAnomaly_Object_Maze::SetElevatorPos()
{
	Elevator->MapPos = ElevatorPoint.Location;
	Elevator->EndPos = ElevatorPoint.Location + FVector(0, 0, -300);
	Elevator->SetActorLocation(ElevatorPoint.Location);
	Elevator->SetActorRotation(ElevatorPoint.Rotation);
}

#pragma endregion
