// Copyright by 2026-1 WAP Game 2 team


#include "Actor/Elevator/Elevator_Entrance.h"

AElevator_Entrance::AElevator_Entrance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Entrance = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Entrance"));
	RootComponent = Entrance;
	
	ElevatorSticker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ElevatorSticker"));
	ElevatorSticker->SetupAttachment(RootComponent);
}
