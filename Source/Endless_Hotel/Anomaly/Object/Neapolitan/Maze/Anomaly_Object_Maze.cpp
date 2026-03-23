// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Maze/Anomaly_Object_Maze.h"
#include "Actor/Elevator/Elevator.h"
#include "Character/AI/MazeMonster/MazeMonster.h"
#include "Player/Controller/EHPlayerController.h"
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

void AAnomaly_Object_Maze::StartAI()
{
	MazeMonster->ActivateMob();
	MazeMonster->bIsAttacked = false;
}

#pragma endregion

#pragma region Elevator

void AAnomaly_Object_Maze::SetElevatorPos()
{
	Elevator->SetActorLocation(ElevatorPoint.Location);
	Elevator->SetActorRotation(ElevatorPoint.Rotation);
}

#pragma endregion
