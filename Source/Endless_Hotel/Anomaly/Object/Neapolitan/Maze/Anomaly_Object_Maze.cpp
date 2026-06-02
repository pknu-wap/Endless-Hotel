// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Maze/Anomaly_Object_Maze.h"
#include "Actor/Elevator/Elevator.h"
#include "Character/AI/MazeMonster/MazeMonster.h"
#include "Player/Controller/EHPlayerController.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "Character/AI/BaseAIController.h"
#include "Actor/Elevator/Elevator_Wall.h"
#include "Actor/Elevator/Elevator_Entrance.h"
#include <Kismet/GameplayStatics.h>

#pragma region MazeMonster

void AAnomaly_Object_Maze::StartMazeMonster()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AEHPlayerController* PC = Cast<AEHPlayerController>(Player->GetController());
	FTimerHandle DelayHandle;

	SetElevatorPos();
	StartAI();
	
	if (MazeMonster.IsValid())
	{
		PC->SetHeartbeatSound(MazeMonster.Get());
	}

	GetWorld()->GetTimerManager().SetTimer(DelayHandle, FTimerDelegate::CreateWeakLambda(this, [PC, &DelayHandle, this]()
		{
			PC->SetPlayerInputAble(true);
			GetWorld()->GetTimerManager().ClearTimer(DelayHandle);
		}), 1.5f, false);
}

#pragma endregion

#pragma region AI

void AAnomaly_Object_Maze::ResetAI()
{
	if (AController* MonsterController = MazeMonster->GetController())
	{
		MazeMonster->SetActorLocation(FVector(-4773, -706, -2768));
		MonsterController->UnPossess();
		MonsterController->Destroy();
	}
}

void AAnomaly_Object_Maze::StartAI()
{
	if (!MazeMonster->GetController())
	{
		MazeMonster->SpawnDefaultController();
	}
	MazeMonster->ActivateMob();
	MazeMonster->SetActorLocation(FVector(-4773, -706, -2768));
	MazeMonster->bIsAttacked = false;
}

#pragma endregion

#pragma region Elevator

void AAnomaly_Object_Maze::SetElevator()
{
	auto* Subsystem = GetGameInstance()->GetSubsystem<UGameSystem>();
	Elevator = Subsystem->GetElevatorByID(TakeOnElevatorID);
	ElevatorWall = Elevator->ElevatorUnderWall;
	ElevatorEntrance = Elevator->LinkedEntrance;
}

void AAnomaly_Object_Maze::SetElevatorPos()
{
	auto* Subsystem = GetGameInstance()->GetSubsystem<UGameSystem>();
	Elevator->SetActorLocation(ElevatorPoint.ElevatorLocation);
	Elevator->SetActorRotation(ElevatorPoint.ElevatorRotation);
	ElevatorWall->SetActorLocation(ElevatorPoint.ElevatorWallLocation);
	ElevatorWall->SetActorRotation(ElevatorPoint.ElevatorWallRotation);
	ElevatorWall->StandardLocation = ElevatorPoint.ElevatorWallLocation;
	ElevatorEntrance->SetActorLocation(ElevatorPoint.ElevatorEntranceLocation);
	ElevatorEntrance->SetActorRotation(ElevatorPoint.ElevatorEntranceRotation);
}

#pragma endregion