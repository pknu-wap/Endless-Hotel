// Copyright by 2025-2 WAP Game 2 team

#include "Component/Elevator/ElevatorCinematicComponent.h"
#include "Component/Elevator/ElevatorDoorComponent.h"
#include "Component/Elevator/ElevatorPassengerComponent.h"
#include "GameSystem/SubSystem/ElevatorManagerSubsystem.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include "GameSystem/SubSystem/DataLayerStreamingSubsystem.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include <Components/AudioComponent.h>
#include <Components/SceneComponent.h>
#include <Components/TimelineComponent.h>
#include <Curves/CurveFloat.h>
#include <Engine/World.h>

#pragma region Base

void UElevatorCinematicComponent::Init(USceneComponent* InTarget, UElevatorDoorComponent* InDoor,
    UElevatorPassengerComponent* InPassenger, UAudioComponent* InMoveAC, UTimelineComponent* InTimeline)
{
    Target = InTarget;
    Door = InDoor;
    Passenger = InPassenger;
    MoveAC = InMoveAC;
    RideTimeline = InTimeline;
}

void UElevatorCinematicComponent::BeginPlay()
{
    Super::BeginPlay();

    if (Target)
    {
        BaseLocation = Target->GetRelativeLocation();
    }

    if (Role != EElevatorCinematicRole::Hallway || !RideTimeline || !RideCurve)
    {
        return;
    }

    FOnTimelineFloat UpdateFunc;
    UpdateFunc.BindUFunction(this, FName("HandleTimelineUpdate"));
    RideTimeline->AddInterpFloat(RideCurve, UpdateFunc);

    FOnTimelineEvent FinishedFunc;
    FinishedFunc.BindUFunction(this, FName("HandleTimelineFinished"));
    RideTimeline->SetTimelineFinishedFunc(FinishedFunc);
}

#pragma endregion

#pragma region Ride

bool UElevatorCinematicComponent::PrepareRide() const
{
    if (!IsHallwayRideActive())
    {
        return false;
    }
    Target->SetRelativeLocation(GetRideStart());
    return true;
}

void UElevatorCinematicComponent::BeginRide()
{
    LoopsLeft = RideLoopCount;
    Door->SetDoorLighting(false);
    if (MoveAC && !MoveAC->IsPlaying())
    {
        MoveAC->Play();
    }
    StartSegment();
}

void UElevatorCinematicComponent::CancelRide()
{
    LoopsLeft = 0;
    if (RideTimeline)
    {
        RideTimeline->Stop();
    }
}

bool UElevatorCinematicComponent::IsHallwayRideActive() const
{
    if (Role != EElevatorCinematicRole::Hallway)
    {
        return false;
    }
    const auto* GameSys = GetWorld()->GetGameInstance()->GetSubsystem<UGameSystem>();
    return GameSys && GameSys->GetGameProgression() == EGameProgression::CheckIn;
}

void UElevatorCinematicComponent::StartSegment() const
{
    Target->SetRelativeLocation(GetRideStart());
    const float MoveDuration = LoopsLeft == 1 ? SegmentDuration / 2 : SegmentDuration; 
    RideTimeline->SetPlayRate(1.f / MoveDuration);
    RideTimeline->PlayFromStart();
}

void UElevatorCinematicComponent::FinishRide() const
{
    if (MoveAC)
    {
        MoveAC->Stop();
    }
    Door->MoveDoors(true);
}

FVector UElevatorCinematicComponent::GetRideEnd() const
{
    return LoopsLeft == 1 ? BaseLocation + LastSegmentOffset : BaseLocation + RideEndOffset;
}

void UElevatorCinematicComponent::HandleTimelineUpdate(float Alpha) const
{
    Target->SetRelativeLocation(FMath::Lerp(GetRideStart(), GetRideEnd(), Alpha));
}

void UElevatorCinematicComponent::HandleTimelineFinished()
{
    Target->SetRelativeLocation(GetRideEnd());

    if (auto* FloorSys = GetWorld()->GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>())
    {
        FloorSys->AdvanceScriptedFloor();
    }
    if (--LoopsLeft == 0)
    {
        FinishRide();
        return;
    }

    const FElevatorPassengerSnapshot Snap = Passenger->Capture();
    StartSegment();
    Passenger->Restore(Snap);
}

#pragma endregion

#pragma region Handoff

bool UElevatorCinematicComponent::HandleDepartureFinished()
{
    if (Role != EElevatorCinematicRole::Lobby)
    {
        return false;
    }

    auto* GI = GetWorld()->GetGameInstance<UEHGameInstance>();
    auto* ElevSub = GI->GetSubsystem<UElevatorManagerSubsystem>();
    auto* DLSub = GI->GetSubsystem<UDataLayerStreamingSubsystem>();

    ElevSub->StorePassenger(Passenger->Capture());
    ElevSub->SetTargetElevator(NextElevatorID);

    DLSub->OnDataLayerReady.AddUObject(this, &UElevatorCinematicComponent::OnLayerReady);
    if (!GI->SwitchDataLayer(NextLayer))
    {
        OnLayerReady();
    }
    return true;
}

void UElevatorCinematicComponent::OnLayerReady() const
{
    auto* GI = GetWorld()->GetGameInstance();
    GI->GetSubsystem<UDataLayerStreamingSubsystem>()->OnDataLayerReady.RemoveAll(this);
    if (MoveAC)
    {
        MoveAC->Stop();
    }
    GI->GetSubsystem<UElevatorManagerSubsystem>()->StartAllElevator();
}

#pragma endregion