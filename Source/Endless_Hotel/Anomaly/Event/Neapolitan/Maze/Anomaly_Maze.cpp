// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/Neapolitan/Maze/Anomaly_Maze.h"
#include "Anomaly/Object/Neapolitan/Maze/Anomaly_Object_Maze.h"
#include "Player/Controller/EHPlayerController.h"
#include "Anomaly/Object/Neapolitan/Doll/Anomaly_Object_Doll.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "Actor/Elevator/Elevator_Wall.h"
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>

#pragma region Anomaly

void AAnomaly_Maze::SetAnomalyState()
{
	Super::SetAnomalyState();

	SetupAnomalyAction(&AAnomaly_Object_Maze::ResetAI);

	TArray<AAnomaly_Object_Maze*> TargetWalls;

	for (const auto& TargetObject : TargetAnomalyObjects)
	{
		auto* Target = Cast<AAnomaly_Object_Maze>(TargetObject);
		if (Target)
		{
			TargetWalls.Add(Target);
		}
	}

	const uint8 MaxIndex = TargetWalls.Num() - 1;
	const uint8 PositionIndex = FMath::RandRange(0, MaxIndex);

	AAnomaly_Object_Maze* TargetWall = TargetWalls[PositionIndex];
	if (TargetWall)
	{
		TargetWall->SetElevator();
		TargetWall->SetDeactiveWall();
		TargetWall->StartMazeMonster();
	}

	switch (AnomalyName)
	{
	case EAnomalyID::Maze_Monster:
		ScheduleAnomaly();
		break;
	case EAnomalyID::Maze_Doll:
		SetupAnomalyAction(&AAnomaly_Object_Doll::ActivateDoll_Show, { EInteractType::Burn });
		ScheduleAnomaly();
	}
}

#pragma endregion