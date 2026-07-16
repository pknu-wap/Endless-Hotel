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
	switch (AnomalyID)
	{
	case EAnomalyID::Maze_Monster:
	{
		TArray<AAnomaly_Object_Maze*> Walls;
		for (const auto& Wall : TargetAnomalyObjects)
		{
			if (AAnomaly_Object_Maze* MazeWall = Cast<AAnomaly_Object_Maze>(Wall))
			{
				Walls.Add(MazeWall);
			}
		}

		if (Walls.Num() > 0)
		{
			const int32 PositionIndex = FMath::RandRange(0, Walls.Num() - 1);
			TargetWall = Walls[PositionIndex];
		}
		SetupAnomalyAction(&AAnomaly_Object_Doll::ActivateDoll_Show, { EInteractType::Burn });
		ScheduleAnomaly();
		TargetWall->StartMazeMonster();
		break;
	}
	}
}

void AAnomaly_Maze::InteractSolveVerdict()
{
	Super::InteractSolveVerdict();

	if (bIsSolved && IsValid(TargetWall.Get()))
	{
		TargetWall->SetDeactiveWall();
	}
}

void AAnomaly_Maze::DisableAnomaly()
{
	if (IsValid(TargetWall.Get()))
	{
		TargetWall->DisableAI();
	}
	Super::DisableAnomaly();
}

#pragma endregion