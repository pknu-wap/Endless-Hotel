// Copyright by 2026-1 WAP Game 2 team

#include "Component/Elevator/ElevatorDoorComponent.h"
#include <Components/AudioComponent.h>
#include <Components/TimelineComponent.h>
#include <Components/BoxComponent.h>

#pragma region Base

void UElevatorDoorComponent::Init(UStaticMeshComponent* InLeftDoor, UStaticMeshComponent* InRightDoor,
	UAudioComponent* InDoorAC, UBoxComponent* InBlockBox, UTimelineComponent* InTimeline, const FElevatorDoorConfig& InConfig)
{
	LeftDoor = InLeftDoor;
	RightDoor = InRightDoor;
	DoorAC = InDoorAC;
	BlockBox = InBlockBox;
	DoorTimeline = InTimeline;
	DoorCurve = InConfig.Curve;
	LeftClosed = InConfig.LeftClosed;
	RightClosed = InConfig.RightClosed;
	LeftOpen = InConfig.LeftOpen;
	RightOpen = InConfig.RightOpen;
	BlockBoxActiveExtent = InConfig.BlockBoxActiveExtent;
}


void UElevatorDoorComponent::BeginPlay()
{
	Super::BeginPlay();
	
	FOnTimelineFloat UpdateFunc;
	UpdateFunc.BindUFunction(this, FName("HandleTimelineUpdate"));
	DoorTimeline->AddInterpFloat(DoorCurve, UpdateFunc);
	FOnTimelineEvent FinishedFunc;
	FinishedFunc.BindUFunction(this, FName("HandleTimelineFinished"));
	DoorTimeline->SetTimelineFinishedFunc(FinishedFunc);
}

#pragma endregion

#pragma region Move Doors

void UElevatorDoorComponent::MoveDoors(bool bWillOpen)
{
	bIsOpened = bWillOpen;
	DoorAC->Activate(true);
	DoorAC->Play();
	DoorTimeline->Stop();

	if (bWillOpen)
	{
		DoorTimeline->PlayFromStart();
		SetDoorLighting(true);
	}
	else
	{
		DoorTimeline->ReverseFromEnd();
	}
}

void UElevatorDoorComponent::ResetDoor()
{
	DoorTimeline->Stop();
	bIsOpened = false;
	bIsMoving = false;
	LeftDoor->SetRelativeLocation(LeftClosed);
	RightDoor->SetRelativeLocation(RightClosed);
	SetDoorLighting(true);
}

void UElevatorDoorComponent::SetDoorLighting(const bool bVisibleFromOutside) const
{
	LeftDoor->SetLightingChannels(bVisibleFromOutside, true, false);
	RightDoor->SetLightingChannels(bVisibleFromOutside, true, false);
}

void UElevatorDoorComponent::HandleTimelineUpdate(float Alpha)
{
	bIsMoving = true;
	LeftDoor->SetRelativeLocation(FMath::Lerp(LeftClosed, LeftOpen, Alpha));
	RightDoor->SetRelativeLocation(FMath::Lerp(RightClosed, RightOpen, Alpha));
	SetActiveBlockBox(true);
}

void UElevatorDoorComponent::HandleTimelineFinished()
{
	bIsMoving = false;
	DoorAC->Stop();
	SetActiveBlockBox(false);
	OnDoorFinished.Broadcast(bIsOpened);
}

void UElevatorDoorComponent::SetActiveBlockBox(const bool bShouldBlock) const
{
	BlockBox->SetCollisionEnabled(bShouldBlock ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
	BlockBox->SetBoxExtent(bShouldBlock ? BlockBoxActiveExtent : FVector::ZeroVector);
}

#pragma endregion