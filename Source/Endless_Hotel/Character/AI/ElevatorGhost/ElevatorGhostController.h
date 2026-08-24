// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Character/AI/BaseAIController.h"
#include <CoreMinimal.h>
#include <ElevatorGhostController.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AElevatorGhostController : public ABaseAIController
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void OnPossess(APawn* InPawn) override;

#pragma endregion

#pragma region Ghost

protected:
	UPROPERTY(EditAnywhere, Category = "Ghost|Moving")
	float WaitTime = 3.f;

	UPROPERTY(EditAnywhere, Category = "Ghost|Moving")
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, Category = "Ghost|Moving")
	FRotator TargetRotation;

	FTimerHandle MoveDelayHandle;

	UPROPERTY(VisibleAnywhere, Category = "Ghost")
	TWeakObjectPtr<class AElevatorGhost> ElevatorGhost;

#pragma endregion

#pragma region Elevator

public:
	UPROPERTY(VisibleAnywhere, Category = "Elevator")
	TWeakObjectPtr<class AElevator> TargetElevator;

#pragma endregion

#pragma region Move

private:
	void StartWalkingIntoElevator();
	void OnGhostReachedElevator();

protected:
	UPROPERTY(EditAnywhere, Category = "Move")
	float WalkSpeed;

private:
	UPROPERTY(EditAnywhere, Category = "Look")
	float LookAtDelay = 2.f;

	FTimerHandle EnterElevatorHandle;
	FTimerHandle LookAtDelayHandle;

#pragma endregion

};