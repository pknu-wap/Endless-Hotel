// Copyright by 2025-2 WAP Game 2 team

#include "Elevator.h"
#include "Actor/Elevator/Elevator_Button.h"
#include "Component/Elevator/ElevatorDoorComponent.h"
#include "Component/Elevator/ElevatorMoveComponent.h"
#include "Component/Elevator/ElevatorPassengerComponent.h"
#include "Component/Elevator/ElevatorGameFlowComponent.h"
#include "Anomaly/Event/Anomaly_Event.h"
#include "Actor/Elevator/Elevator_Wall.h"
#include "Actor/Elevator/Elevator_Entrance.h"
#include "GameSystem/SubSystem/ElevatorManagerSubsystem.h"
#include "Type/Level/Type_Level.h"
#include <Components/StaticMeshComponent.h>
#include <Components/PointLightComponent.h>
#include <Components/TimelineComponent.h>
#include <Components/AudioComponent.h>
#include <Components/BoxComponent.h>

#pragma region Base

AElevator::AElevator(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    Exterior_Structure = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Exterior_Structure"));
    RootComponent = Exterior_Structure;

    Car = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Car"));
    Car->SetupAttachment(RootComponent);

    LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
    LeftDoor->SetupAttachment(Car);
    LeftGlass = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftGlass"));
    LeftGlass->SetupAttachment(LeftDoor);

    RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));
    RightDoor->SetupAttachment(Car);
    RightGlass = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightGlass"));
    RightGlass->SetupAttachment(RightDoor);

    DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeline"));
    DoorComp = CreateDefaultSubobject<UElevatorDoorComponent>(TEXT("DoorComp"));

    MoveTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("MoveTimeline"));
    MoveComp = CreateDefaultSubobject<UElevatorMoveComponent>(TEXT("MoveComp"));
    
    PassengerComp = CreateDefaultSubobject<UElevatorPassengerComponent>(TEXT("PassengerComp"));
    VerdictComp = CreateDefaultSubobject<UElevatorGameFlowComponent>(TEXT("VerdictComp"));

    Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
    Floor->SetupAttachment(Car);

    ElevatorLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("ElevatorLight"));
    ElevatorLight->SetupAttachment(Car);

    Door_AC = CreateDefaultSubobject<UAudioComponent>(TEXT("Door AC"));
    Door_AC->SetupAttachment(Car);

    Move_AC = CreateDefaultSubobject<UAudioComponent>(TEXT("Move_AC"));
    Move_AC->SetupAttachment(RootComponent);
    Move_AC->bAutoActivate = false;
    Move_AC->bAllowSpatialization = false;
    
    Bell_AC = CreateDefaultSubobject<UAudioComponent>(TEXT("Bell_AC"));
    Bell_AC->SetupAttachment(Car);
    Bell_AC->bAutoActivate = false;

    TriggerBlockBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBlockBox"));
    TriggerBlockBox->SetBoxExtent(BlockBoxActiveExtent);
    TriggerBlockBox->SetupAttachment(Car);
    TriggerBlockBox->SetCollisionProfileName(TEXT("TriggerBlockBox"));

    TeleportAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("TeleportAnchor"));
    TeleportAnchor->SetupAttachment(RootComponent);
}

void AElevator::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    FElevatorDoorConfig DoorCfg;
    DoorCfg.Curve = DoorCurve;
    DoorCfg.LeftClosed = LeftDoorClosed;
    DoorCfg.RightClosed = RightDoorClosed;
    DoorCfg.LeftOpen = LeftDoorOpenPos;
    DoorCfg.RightOpen = RightDoorOpenPos;
    DoorCfg.BlockBoxActiveExtent = BlockBoxActiveExtent;
    DoorComp->Init(LeftDoor, RightDoor, Door_AC, TriggerBlockBox, DoorTimeline, DoorCfg);

    FElevatorMoveConfig MoveCfg;
    MoveCfg.Curve = MoveCurve;
    MoveCfg.StandardPos = StandardPos;
    MoveCfg.StartPos = StartPos;
    MoveCfg.MapPos = MapPos;
    MoveCfg.EndPos = EndPos;
    MoveCfg.RideStartPos = RideStartPos;
    MoveCfg.RideEndPos = RideEndPos;
    MoveComp->Init(RootComponent, Move_AC, MoveTimeline, MoveCfg);
    MoveComp->OnMoveFinished.AddUObject(this, &AElevator::HandleMoveFinished);
    PassengerComp->Init(TeleportAnchor, Exterior_Structure, Car);
}

void AElevator::BeginPlay()
{
    Super::BeginPlay();

    auto* Sub = GetGameInstance()->GetSubsystem<UElevatorManagerSubsystem>();
    Sub->RegisterElevator(this);
    
    if(InsideButton.IsValid())
    {
        InsideButton->OnButtonPressed.AddDynamic(this, &AElevator::OnButtonClicked);
    }
    if (EntranceButton.IsValid())
    {
        EntranceButton->OnButtonPressed.AddDynamic(this, &AElevator::OnButtonClicked);
    }
}

void AElevator::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
    Super::EndPlay(EndPlayReason);
}

#pragma endregion

#pragma region Light

void AElevator::SetLightOn(const bool bIsOn) const
{
    const float ElevatorLightIntensity = bIsOn ? LightOnIntensity : LightOffIntensity;
    ElevatorLight->SetIntensity(ElevatorLightIntensity);
}

#pragma endregion

#pragma region Sound

void AElevator::OpenDoorsWithBell()
{
    MoveComp->StopMoveSound();
    auto OpenDoors = [this]()
    {
        MoveDoors(true);
        if (InsideButton.IsValid())
        {
            InsideButton->CanPressButton(true);
        }
    };
    if (BellToDoorDelay > 0.f)
    {
        Bell_AC->Play();
        GetWorld()->GetTimerManager().SetTimer(BellHandle,FTimerDelegate::CreateWeakLambda(this, OpenDoors),BellToDoorDelay, false);
    }
    else
    {
        OpenDoors();
    }
}

#pragma  endregion

#pragma region MovementSettings

void AElevator::PlayArrivalSequence()
{
    CurrentMove = EElevatorMoveKind::Arrival;
    DoorComp->SetDoorLighting(false);
    MoveComp->PlayArrival();
}

void AElevator::PlayDepartureSequence()
{
    CurrentMove = EElevatorMoveKind::Departure;
    DoorComp->SetDoorLighting(false);
    MoveComp->PlayDeparture();
}

void AElevator::HandleMoveFinished()
{
    UE_LOG(LogTemp, Warning, TEXT("[Ride] Arrival IsTop=%d"), VerdictComp->IsTopFloor());
    const EElevatorMoveKind Kind = CurrentMove;
    CurrentMove = EElevatorMoveKind::None;
    const bool bRide = MoveComp->bIsCinematicElevator;

    switch (Kind)
    {
    case EElevatorMoveKind::Arrival:
        if (bRide)
        {
            VerdictComp->ScriptFloor();
            if (VerdictComp->IsTopFloor())
            {
                bIsRiding = false;
                MoveComp->bIsCinematicElevator = false;
                OpenDoorsWithBell();
                break;
            }
            PlayDepartureSequence();
            break;
        }
        OpenDoorsWithBell();
        break;

    case EElevatorMoveKind::Departure:
        if (bRide && bIsLobbyElevator)
        {
            PassengerComp->Store();
            bIsRiding = false;
            VerdictComp->SetTargetElevator("HotelElevator");
            VerdictComp->RequestSwapDataLayer(EMapDataLayer::Hotel);
            break;
        }
        if (bRide)
        {
            const FElevatorPassengerSnapshot Snap = PassengerComp->Capture();
            PlayArrivalSequence();
            PassengerComp->Restore(Snap);
            break;
        }
        if (ElevatorUnderWall.IsValid())
        {
            ElevatorUnderWall->MoveWall(MoveComp->GetMoveDuration());
        }
        GetWorld()->GetTimerManager().SetTimer(MoveHandle,FTimerDelegate::CreateWeakLambda(this, [this]()
        {
            RequestAnomalyVerdict();
        }), MoveComp->GetMoveDuration(), false);
        break;
    }
}

#pragma endregion

#pragma region Door

void AElevator::MoveDoors(bool bWillOpen) const
{
    MoveComp->StopMoveSound();
    DoorComp->MoveDoors(bWillOpen);
}

#pragma endregion

#pragma region Button

void AElevator::OnButtonClicked(bool bIsOpening)
{
    SetLightOn(true);
    MoveDoors(bIsOpening);
    if (!bIsOpening)
    {
        FTimerHandle DoorHandle;
        GetWorld()->GetTimerManager().SetTimer(DoorHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
            {
                PlayDepartureSequence();
            }), DoorDuration, false);
    }
}

#pragma endregion

#pragma region Subsystem

void AElevator::RequestAnomalyVerdict() const
{
    PassengerComp->Store();
    VerdictComp->RequestVerdict();
}

void AElevator::ResetState() const
{
    if (ElevatorUnderWall.IsValid())
    {
        ElevatorUnderWall->ResetWall();
    }
    if (ElevatorOverWall.IsValid())
    {
        ElevatorOverWall->ResetWall();
    }

    DoorComp->ResetDoor();
    Floor->SetVisibility(true);
    Floor->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AElevator::PrepareAsTarget(const UElevatorManagerSubsystem& Sub)
{
    if (LinkedEntrance.IsValid())
    {
        LinkedEntrance->SetTriggerActive();
    }
    if (InsideButton.IsValid())
    {
        InsideButton->CanPressButton(false);
    }
    
    DoorComp->SetDoorLighting(false);
    SetLightOn(true);
    MoveComp->SetToStart();
    PassengerComp->Restore(Sub.GetPassenger());

    if (MoveComp->bIsCinematicElevator)
    {
        bIsRiding = true;
        MoveComp->PlayMoveSound();
        PlayArrivalSequence();
        return;
    }

    if (ElevatorOverWall.IsValid())
    {
        ElevatorOverWall->MoveWall(MoveComp->GetMoveDuration());
    }

    GetWorld()->GetTimerManager().SetTimer(MoveStartHandle,
        FTimerDelegate::CreateWeakLambda(this, [this]()
        {
            PlayArrivalSequence();
        }), MoveComp->GetMoveDuration(), false);
}

void AElevator::PrepareAsNonTarget() const
{
    if (LinkedEntrance.IsValid())
    {
        LinkedEntrance->ResetTrigger();
    }
    if (InsideButton.IsValid())
    {
        InsideButton->CanPressButton(true);
    }

    MoveComp->SetToMap();
    SetLightOn(false);
}

void AElevator::StartElevator()
{
    GetWorld()->GetTimerManager().ClearTimer(BellHandle);
    Bell_AC->Stop();
    if (bIsRiding)
    {
        return;
    }
    if (!VerdictComp->IsCheckIn())
    {
        MoveComp->bIsCinematicElevator = false;
    }
    GetWorld()->GetTimerManager().ClearTimer(MoveStartHandle);
    GetWorld()->GetTimerManager().ClearTimer(MoveHandle);
    PassengerComp->CancelRestore();
    MoveComp->CancelMove();
    CurrentMove = EElevatorMoveKind::None;
    ResetState();
    const auto* Sub = GetGameInstance()->GetSubsystem<UElevatorManagerSubsystem>();
    if (Sub && Sub->IsTargetElevator(this))
    {
        PrepareAsTarget(*Sub);
    }
    else
    {
        PrepareAsNonTarget();
    }
}

#pragma endregion

#pragma region Anomaly

void AElevator::DisableElevatorFloor()
{
    Floor->SetVisibility(false);
    Floor->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AElevator::DisableElevator() const
{
    RootComponent->SetVisibility(false);
}

#pragma endregion