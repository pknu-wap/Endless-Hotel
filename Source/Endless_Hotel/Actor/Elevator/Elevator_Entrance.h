// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Actor/EHActor.h"
#include "Elevator_Entrance.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AElevator_Entrance : public AEHActor
{
	GENERATED_BODY()

#pragma region Base
	
public:
	AElevator_Entrance(const FObjectInitializer& ObjectInitializer);
	
protected:
	UPROPERTY(EditAnywhere, Category="Entrance")
	TObjectPtr<UStaticMeshComponent> Entrance;
	
	UPROPERTY(EditAnywhere, Category="ElevatorSticker")
	TObjectPtr<UStaticMeshComponent> ElevatorSticker;
	
#pragma endregion

};
