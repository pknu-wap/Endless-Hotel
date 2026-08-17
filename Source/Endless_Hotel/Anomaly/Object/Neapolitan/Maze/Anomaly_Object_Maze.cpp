// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Maze/Anomaly_Object_Maze.h"
#include "Actor/Elevator/Elevator.h"
#include "Character/AI/MazeMonster/MazeMonster.h"
#include "Player/Controller/EHPlayerController.h"
#include "GameSystem/SubSystem/ElevatorManagerSubsystem.h"
#include "Character/AI/BaseAIController.h"
#include "Actor/Elevator/Elevator_Wall.h"
#include "Actor/Elevator/Elevator_Entrance.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/CapsuleComponent.h>

#pragma region MazeMonster

void AAnomaly_Object_Maze::StartMazeMonster()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AEHPlayerController* PC = Cast<AEHPlayerController>(Player->GetController());
	FTimerHandle DelayHandle;

	StartAI();
	MazeMonster->PlayHeartbeatSound();
}

void AAnomaly_Object_Maze::SetDeactiveWall()
{
	Object->SetVisibility(false);
	Object->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetElevatorPos();
}

void AAnomaly_Object_Maze::Reset()
{
	Object->SetVisibility(true);
	Object->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

#pragma endregion

#pragma region AI

void AAnomaly_Object_Maze::DisableAI()
{
	if (AController* MonsterController = MazeMonster->GetController())
	{
		MonsterController->UnPossess();
		MonsterController->Destroy();
	}
	if (IsValid(MazeMonster.Get()))
	{
		MazeMonster->Destroy();
		MazeMonster = nullptr;
	}
}

void AAnomaly_Object_Maze::StartAI()
{
	if (!IsValid(MazeMonster.Get()))
	{
		MazeMonster = GetWorld()->SpawnActor<AMazeMonster>(MazeMonsterClass, MazeMonsterTransform);
	}
	MazeMonster->GetCharacterMovement()->GravityScale = 1.f;
	MazeMonster->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	MazeMonster->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MazeMonster->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MazeMonster->bIsAttacked = false;
	if (!MazeMonster->GetController())
	{
		MazeMonster->SpawnDefaultController();
	}
	SetElevator();
}

#pragma endregion

#pragma region Elevator

void AAnomaly_Object_Maze::SetElevator()
{
	auto* ElevatorSub = GetGameInstance()->GetSubsystem<UElevatorManagerSubsystem>();
	Elevator = ElevatorSub->GetElevatorByID(TakeOnElevatorID);
	ElevatorWall = Elevator->ElevatorUnderWall;
	ElevatorEntrance = Elevator->LinkedEntrance;
	Elevator->SetActorLocation(FVector(-5210, 1435, -2927));
	ElevatorEntrance->SetActorLocation(FVector(-5210, 1435, -2927));
	Elevator->StandardPos = FVector(-5210, 1435, -2927);
}

void AAnomaly_Object_Maze::SetElevatorPos()
{
	Elevator->SetActorLocation(ElevatorPoint.ElevatorLocation);
	Elevator->SetActorRotation(ElevatorPoint.ElevatorRotation);
	Elevator->StandardPos = ElevatorPoint.ElevatorLocation;
	ElevatorWall->SetActorLocation(ElevatorPoint.ElevatorWallLocation);
	ElevatorWall->SetActorRotation(ElevatorPoint.ElevatorWallRotation);
	ElevatorWall->StandardLocation = ElevatorPoint.ElevatorWallLocation;
	ElevatorEntrance->SetActorLocation(ElevatorPoint.ElevatorEntranceLocation);
	ElevatorEntrance->SetActorRotation(ElevatorPoint.ElevatorEntranceRotation);
}

#pragma endregion