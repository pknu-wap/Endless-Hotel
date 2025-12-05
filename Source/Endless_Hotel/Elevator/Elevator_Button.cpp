// Copyright by 2025-2 WAP Game 2 team


#include "Elevator/Elevator_Button.h"
#include "Elevator/Elevator.h"

AElevator_Button::AElevator_Button(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	Pannel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button_Mesh"));
	Pannel->SetupAttachment(RootComponent);
	Pannel->SetRelativeLocation(FVector3d(40.f, 47.f, -19.f));

	Up_Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Up_Button"));
	Up_Button->SetupAttachment(Pannel);
	Up_ButtonRing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Up_ButtonRing"));
	Up_ButtonRing->SetupAttachment(Pannel);
	Down_Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Down_Button"));
	Down_Button->SetupAttachment(Pannel);
	Down_ButtonRing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Down_ButtonRing"));
	Down_ButtonRing->SetupAttachment(Pannel);
}

void AElevator_Button::Interacted()
{
	if (OwnerElevator->bIsDoorMoving || OwnerElevator-> bIsDoorOpened) return;
	OwnerElevator->CallElevator();
	FTimerHandle WaitHandle;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateWeakLambda(this, [this]() mutable
		{
			OwnerElevator->TryCloseDoorAfterDelay();
		}), 4.0f, false);
}
