// Copyright by 2026-1 WAP Game 2 team

#include "Actor/Elevator/Elevator_Entrance.h"
#include "Player/Character/EHPlayer.h"
#include "Actor/Elevator/Elevator.h"
#include <Components/BoxComponent.h>

#pragma region Base

AElevator_Entrance::AElevator_Entrance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Entrance = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Entrance"));
	RootComponent = Entrance;

	TakeOff_Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TakeOff_Trigger"));
	TakeOff_Trigger->SetupAttachment(RootComponent);
}

void AElevator_Entrance::BeginPlay()
{
	Super::BeginPlay();
	TakeOff_Trigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TakeOff_Trigger->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnTriggerBox);
}

#pragma endregion

#pragma region Trigger

void AElevator_Entrance::ResetTrigger()
{
	TakeOff_Trigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AElevator_Entrance::SetTriggerActive()
{
	TakeOff_Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AElevator_Entrance::OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEHPlayer* Player = Cast<AEHPlayer>(OtherActor);
	if (!Player)
	{
		return;
	}
	TakeOff_Trigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Elevator->SetActiveBlockBox(true);
	FTimerHandle DoorDelayHandle;
	GetWorld()->GetTimerManager().SetTimer(DoorDelayHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			Elevator->MoveDoors(false);
			Elevator->SetLightOn(false);
		}), DoorDelay, false);
}

#pragma endregion