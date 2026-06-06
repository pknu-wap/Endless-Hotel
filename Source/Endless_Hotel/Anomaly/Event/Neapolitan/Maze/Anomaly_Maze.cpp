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
	SetupAnomalyAction(&AAnomaly_Object_Maze::SetElevator);

	switch (AnomalyName)
	{
	case EAnomalyID::Maze_Monster:
		SetupAnomalyAction(&AAnomaly_Object_Maze::StartMazeMonster);
		SetupAnomalyAction(&AAnomaly_Object_Doll::ActivateDoll_Show, { EInteractType::Burn });
		ScheduleAnomaly();
		break;
	}
}

void AAnomaly_Maze::InteractSolveVerdict()
{
	Super::InteractSolveVerdict();
	if (bIsSolved)
	{
		TArray<AAnomaly_Object_Maze*> Walls;
		for(const auto& Wall : TargetAnomalyObjects)
		{
			if(Cast<AAnomaly_Object_Maze>(Wall))
			{
				Walls.Add(Cast<AAnomaly_Object_Maze>(Wall));
			}
		}
		const uint8 MaxIndex = Walls.Num() - 1;
		const uint8 PositionIndex = FMath::RandRange(0, MaxIndex);

		AAnomaly_Object_Maze* TargetWall = Walls[PositionIndex];
		if (TargetWall)
		{
			TargetWall->SetDeactiveWall();
		}
	}
}

#pragma endregion