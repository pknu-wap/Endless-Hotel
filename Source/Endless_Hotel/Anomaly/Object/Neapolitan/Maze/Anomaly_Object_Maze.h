// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Object/Anomaly_Object_Neapolitan.h"
#include "Anomaly_Object_Maze.generated.h"

#pragma region Declare

USTRUCT(BlueprintType)
struct FMazeElevatorSetting
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere) FVector Location;
	UPROPERTY(EditAnywhere) FRotator Rotation;
};

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Maze : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_Maze(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region MazeMonster

public:
	void StartMazeMonster();

#pragma endregion

#pragma region Elevator

private:
	void RandomizeElevatorLocation();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<AElevator> Elevator;

	UPROPERTY(EditAnywhere)
	TArray<FMazeElevatorSetting> ElevatorPoint;

#pragma endregion

#pragma region Wall

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TArray<TObjectPtr<UChildActorComponent>> WallComponents;

#pragma endregion

};
