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

void AAnomaly_Maze::StartAnomalyAction()
{
	switch (AnomalyName)
	{
	case EAnomalyID::Maze_Monster:
		MazeMonster();
		break;
	case EAnomalyID::Maze_Doll:
		Super::StartAnomalyAction();
		break;
	}
}

#pragma endregion

#pragma region MazeMonster

void AAnomaly_Maze::MazeMonster()
{
	const uint8 MaxIndex = TargetAnomalyObjects.Num() - 1;
	const uint8 PositionIndex = FMath::RandRange(0, MaxIndex);

	AAnomaly_Object_Base* TargetWall = TargetAnomalyObjects[PositionIndex];
	if (TargetWall)
	{
		TargetWall->SetActorEnableCollision(false);
		TargetWall->SetActorHiddenInGame(true);
	}

	if (AAnomaly_Object_Maze* MazeObject = Cast<AAnomaly_Object_Maze>(TargetWall))
	{
		auto* Subsystem = GetGameInstance()->GetSubsystem<UGameSystem>();
		MazeObject->SetElevator(Subsystem->GetElevatorByID(TakeOnElevatorID));
		MazeObject->StartMazeMonster();
	}
}

#pragma endregion