// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Maze.generated.h>

#pragma region Declare

USTRUCT(BlueprintType)
struct FMazeElevatorSetting
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	FVector ElevatorLocation = FVector::ZeroVector;
	
	UPROPERTY(EditAnywhere)
	FRotator ElevatorRotation = FRotator::ZeroRotator;
	
	UPROPERTY(EditAnywhere)
	FVector ElevatorWallLocation = FVector::ZeroVector;
	
	UPROPERTY(EditAnywhere)
	FRotator ElevatorWallRotation = FRotator::ZeroRotator;
	
	UPROPERTY(EditAnywhere)
	FVector ElevatorEntranceLocation = FVector::ZeroVector;
	
	UPROPERTY(EditAnywhere)
	FRotator ElevatorEntranceRotation = FRotator::ZeroRotator;
};

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Maze : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()

#pragma region Anomaly

public:
	void StartMazeMonster();
	void SetDeactiveWall();
	virtual void Reset() override;

#pragma endregion

#pragma region AI

public:
	UFUNCTION()
	void ResetAI();

private:
	void StartAI();

#pragma endregion

#pragma region Elevator

public:
	void SetElevator();

private:
	void SetElevatorPos();

protected:
	UPROPERTY(EditAnywhere, Category = "MazeTakeonElevatorID")
	FName TakeOnElevatorID;

	UPROPERTY(EditAnywhere, Category = "Elevator")
	TWeakObjectPtr<class AElevator> Elevator;

	UPROPERTY(EditAnywhere, Category = "Elevator")
	TWeakObjectPtr<class AElevator_Wall> ElevatorWall;

	UPROPERTY(EditAnywhere, Category = "Elevator")
	TWeakObjectPtr<class AElevator_Entrance> ElevatorEntrance;

	UPROPERTY(EditAnywhere, Category = "Elevator")
	FMazeElevatorSetting ElevatorPoint;

	UPROPERTY(EditAnywhere, Category = "AI")
	TWeakObjectPtr<class AMazeMonster> MazeMonster;

#pragma endregion

};