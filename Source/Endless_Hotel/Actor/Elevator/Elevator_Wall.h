// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Actor/EHActor.h"
#include "Elevator_Wall.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AElevator_Wall : public AEHActor
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AElevator_Wall(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION()
	void ResetWall();

protected:
	UPROPERTY(EditAnywhere, Category="Wall")
	TObjectPtr<UStaticMeshComponent> Wall;

#pragma endregion

#pragma region Move

public:
	void MoveWall(float MoveDuration);

public:
	UPROPERTY(EditAnywhere, Category = "Move")
	FVector StandardLocation;

protected:
	UPROPERTY(EditAnywhere, Category = "Move")
	FVector Start;

	UPROPERTY(EditAnywhere, Category = "Move")
	FVector End;

	UPROPERTY(EditAnywhere, Category = "Move")
	bool bIsOver;

#pragma endregion

};