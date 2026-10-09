// Copyright by 2026-1 WAP Game 2 team

#include "Component/Elevator/ElevatorMoveComponent.h"
#include <Components/AudioComponent.h>
#include <Components/TimelineComponent.h>
#include <Curves/CurveFloat.h>

#pragma region Base

void UElevatorMoveComponent::Init(USceneComponent* InTarget, UAudioComponent* InMoveAC, UTimelineComponent* InTimeline, const FElevatorMoveConfig& InConfig)
{
    MoveTarget = InTarget;
    MoveAC = InMoveAC;
    MoveTimeline = InTimeline;
    Config = InConfig;
}

void UElevatorMoveComponent::BeginPlay()
{
    Super::BeginPlay();
    
    FOnTimelineFloat UpdateFunc;
    UpdateFunc.BindUFunction(this, FName("HandleTimelineUpdate"));
    MoveTimeline->AddInterpFloat(Config.Curve, UpdateFunc);

    FOnTimelineEvent FinishedFunc;
    FinishedFunc.BindUFunction(this, FName("HandleTimelineFinished"));
    MoveTimeline->SetTimelineFinishedFunc(FinishedFunc);
}

#pragma endregion

#pragma region Move

void UElevatorMoveComponent::SetToStart()
{
    CancelMove();
    MoveTarget->SetRelativeLocation(GetStartLocation());
}

void UElevatorMoveComponent::SetToMap()
{
    CancelMove();
    MoveTarget->SetRelativeLocation(GetMapLocation());
}

void UElevatorMoveComponent::PlayArrival()
{
    BeginMove(GetStartLocation(), GetMapLocation());
}

void UElevatorMoveComponent::PlayDeparture()
{
    if (MoveAC && !MoveAC->IsPlaying())
    {
        MoveAC->Play();
    }
    BeginMove(GetMapLocation(), GetEndLocation());
}

void UElevatorMoveComponent::CancelMove()
{
    bIsMoving = false;
    if (MoveTimeline)
    {
        MoveTimeline->Stop();
    }
}

void UElevatorMoveComponent::StopMoveSound() const
{
    if (MoveAC && MoveAC->IsPlaying())
    {
        MoveAC->Stop();
    }
}

void UElevatorMoveComponent::BeginMove(const FVector& From, const FVector& To)
{
    MoveFrom = From;
    MoveTo = To;
    bIsMoving = true;
    MoveTarget->SetRelativeLocation(From);

    MoveTimeline->SetPlayRate(1.f / MoveDuration);
    MoveTimeline->PlayFromStart();
}

void UElevatorMoveComponent::HandleTimelineUpdate(float Alpha)
{
    MoveTarget->SetRelativeLocation(FMath::Lerp(MoveFrom, MoveTo, Alpha));
}

void UElevatorMoveComponent::HandleTimelineFinished()
{
    MoveTarget->SetRelativeLocation(MoveTo);
    bIsMoving = false;
    OnMoveFinished.Broadcast();
}

#pragma endregion