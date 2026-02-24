// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Neapolitan/Maze/Anomaly_Maze.h"
#include "Anomaly/Object/Neapolitan/Maze/Anomaly_Object_Maze.h"
#include <Kismet/GameplayStatics.h>

#pragma region Base

AAnomaly_Maze::AAnomaly_Maze(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PlayerStartTransform.SetLocation(FVector(-3790, 640, -2852));
}

#pragma endregion

#pragma region Anomaly

void AAnomaly_Maze::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();

	switch (AnomalyName)
	{
	case EAnomalyName::Maze_Monster:
		ScheduleAnomaly();
		break;
	}
}

void AAnomaly_Maze::StartAnomalyAction()
{
	switch (AnomalyName)
	{
	case EAnomalyName::Maze_Monster:
		MazeMonster();
		break;
	}
}

#pragma endregion

#pragma region MazeMonster

void AAnomaly_Maze::MazeMonster()
{
	const uint8 MaxIndex = LinkedObjects.Num() - 1;
	const uint8 PositionIndex = FMath::RandRange(0, MaxIndex);

	AActor* TargetWall = LinkedObjects[PositionIndex];

	TargetWall->SetActorEnableCollision(false);
	TargetWall->SetActorHiddenInGame(true);

	if (AAnomaly_Object_Maze* MazeObject = Cast<AAnomaly_Object_Maze>(TargetWall))
	{
		MazeObject->StartMazeMonster();
	}
}

#pragma endregion
