// Copyright by 2025-2 WAP Game 2 team

#include "Elevator.h"
#include "Actor/Elevator/Elevator_Button.h"
#include "Component/Elevator/ElevatorDoorComponent.h"
#include "Anomaly/Event/Anomaly_Event.h"
#include "Player/Controller/EHPlayerController.h"
#include "Actor/Elevator/Elevator_Wall.h"
#include "Actor/Elevator/Elevator_Entrance.h"
#include "GameSystem/SubSystem/ElevatorManagerSubsystem.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include <Components/StaticMeshComponent.h>
#include <Components/PointLightComponent.h>
#include <Components/TimelineComponent.h>
#include <Components/AudioComponent.h>
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>
#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>

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

    TriggerBlockBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBlockBox"));
    TriggerBlockBox->SetBoxExtent(BlockBoxActiveExtent);
    TriggerBlockBox->SetupAttachment(Car);
    TriggerBlockBox->SetCollisionProfileName(TEXT("TriggerBlockBox"));

    TeleportAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("TeleportAnchor"));
    TeleportAnchor->SetupAttachment(RootComponent);
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

void AElevator::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    FElevatorDoorConfig Cfg;
    Cfg.Curve = DoorCurve;
    Cfg.LeftClosed = LeftDoorClosed;
    Cfg.RightClosed = RightDoorClosed;
    Cfg.LeftOpen = LeftDoorOpenPos;
    Cfg.RightOpen = RightDoorOpenPos;
    Cfg.BlockBoxActiveExtent = BlockBoxActiveExtent;
    DoorComp->Init(LeftDoor, RightDoor, Door_AC, TriggerBlockBox, DoorTimeline, Cfg);
}

#pragma endregion

#pragma region Light

void AElevator::SetLightOn(bool bIsOn)
{
    if (bIsOn)
    {
        ElevatorLight->SetIntensity(LightOnIntensity);
    }
    else
    {
        ElevatorLight->SetIntensity(LightOffIntensity);
    }
}

#pragma endregion

#pragma region MovementSettings

void AElevator::MoveElevator(FVector Start, FVector End, bool bIsStart)
{
    RootComponent->SetRelativeLocation(Start);
    DoorComp->SetDoorLighting(false);
    if(!Move_AC->IsPlaying() && !bIsStart)
    {
        Move_AC->Play();
    }
    FLatentActionInfo LatentInfo;
    LatentInfo.CallbackTarget = this;
    LatentInfo.UUID = __LINE__;
    LatentInfo.Linkage = 0;
    
    UKismetSystemLibrary::MoveComponentTo(RootComponent, End, RootComponent->GetComponentRotation(), false, false, ElevatorMoveDuration, false, EMoveComponentAction::Move, LatentInfo);

    FTimerHandle ElevatorWallHandle;
    FTimerHandle StartDelayHandle;
    auto SetDelay = [this](FTimerHandle& Handle, TFunction<void()> Func, float Delay)
        {
            GetWorld()->GetTimerManager().SetTimer(Handle,
                FTimerDelegate::CreateWeakLambda(this, MoveTemp(Func)), Delay, false);
        };

    if (bIsStart)
    {
        SetDelay(StartDelayHandle, [this] 
            { 
                MoveDoors(true);
                if(InsideButton.IsValid())
                {
                    InsideButton->CanPressButton(true);
                }
            }, ElevatorMoveDuration + 0.1f);
    }
    else
    {
        SetDelay(ElevatorWallHandle, [this]
            { 
                if(ElevatorUnderWall.IsValid())
                {
                    ElevatorUnderWall->MoveWall(ElevatorMoveDuration);
                }
            }, ElevatorMoveDuration + 0.1f);
        SetDelay(StartDelayHandle, [this] { NotifySubsystem(); }, ElevatorMoveDuration * 2.0f);
    }
}

#pragma endregion

#pragma region Door

void AElevator::MoveDoors(bool bWillOpen)
{
    if (Move_AC->IsPlaying())
    {
        Move_AC->Stop();
    }
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
                MoveElevator(StandardPos + MapPos, StandardPos + EndPos, false);
            }), DoorDuration, false);
    }
}

#pragma endregion

#pragma region Subsystem

void AElevator::NotifySubsystem() const
{
    const auto* GI = GetGameInstance();
    auto* VerdictSub = GI->GetSubsystem<UAnomalyVerdictSubsystem>();
    auto* ElevatorSub = GI->GetSubsystem<UElevatorManagerSubsystem>();
    VerdictSub->SetIsElevatorNormal(bIsNormalElevator);
    VerdictSub->TryInteractSolveVerdict();
    ElevatorSub->StorePassenger(CapturePassenger());
    VerdictSub->ApplyVerdict();
}

void AElevator::ResetState()
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
    RootComponent->SetRelativeLocation(StandardPos + StartPos);

    RestorePassenger(Sub.GetPassenger());

    if (ElevatorOverWall.IsValid())
    {
        ElevatorOverWall->MoveWall(ElevatorMoveDuration);
    }

    GetWorld()->GetTimerManager().SetTimer(MoveStartHandle,
        FTimerDelegate::CreateWeakLambda(this, [this]()
        {
            MoveElevator(StandardPos + StartPos, StandardPos + MapPos, true);
        }), ElevatorMoveDuration, false);
}

void AElevator::PrepareAsNonTarget()
{
    if (LinkedEntrance.IsValid())
    {
        LinkedEntrance->ResetTrigger();
    }
    if (InsideButton.IsValid())
    {
        InsideButton->CanPressButton(true);
    }

    Exterior_Structure->SetRelativeLocation(StandardPos + MapPos);
    SetLightOn(false);
}

void AElevator::RestorePassenger(const FElevatorPassengerSnapshot& Snap)
{
    auto* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    auto* PC = Cast<AEHPlayerController>(Player->GetController());
    auto* CMC = Player->GetCharacterMovement();

    Exterior_Structure->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Car->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    const FRotator ControlRot = Snap.ControlRotation - (Snap.SourceElevatorRotation - GetActorRotation());
    const FVector TargetLocation = TeleportAnchor->GetComponentTransform().TransformPosition(Snap.LocalLocation);

    Player->SetActorLocation(TargetLocation, false, nullptr, ETeleportType::TeleportPhysics);
    Player->SetActorRotation(FRotator(0.f, ControlRot.Yaw, ControlRot.Roll));
    PC->SetControlRotation(ControlRot);
    PC->PlayerCameraManager->SetGameCameraCutThisFrame();

    Player->SetBase(nullptr);
    Player->SetActorEnableCollision(true);

    const FVector Forward = Player->GetActorForwardVector();
    CMC->Velocity = FVector(Forward.X, Forward.Y, 0.f) * Snap.HorizontalSpeed;
    CMC->SetMovementMode(MOVE_Falling);

    GetWorld()->GetTimerManager().SetTimer(CollisionRestoreHandle,
        FTimerDelegate::CreateWeakLambda(this, [this]()
        {
            Exterior_Structure->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
            Car->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        }), 0.05f, false);
}

FElevatorPassengerSnapshot AElevator::CapturePassenger() const
{
    FElevatorPassengerSnapshot Snap;
    auto* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    const auto* PC = Player->GetController();
    const auto* CMC = Player->GetCharacterMovement();
    Snap.LocalLocation = TeleportAnchor->GetComponentTransform().InverseTransformPosition(Player->GetActorLocation());
    Snap.SourceElevatorRotation = GetActorRotation();
    if (PC)
    {
        Snap.ControlRotation = PC->GetControlRotation();
    }
    if (CMC)
    {
        Snap.HorizontalSpeed = FVector(CMC->Velocity.X, CMC->Velocity.Y, 0.f).Size();
    }
    return Snap;
}

void AElevator::StartElevator()
{
    GetWorld()->GetTimerManager().ClearTimer(MoveStartHandle);
    GetWorld()->GetTimerManager().ClearTimer(CollisionRestoreHandle);

    ResetState();

    auto* Sub = GetGameInstance()->GetSubsystem<UElevatorManagerSubsystem>();
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