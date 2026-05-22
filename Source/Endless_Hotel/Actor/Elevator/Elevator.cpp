// Copyright by 2025-2 WAP Game 2 team

#include "Elevator.h"
#include "Actor/Elevator/Elevator_Button.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "Anomaly/Base/Anomaly_Event.h"
#include "Player/Character/EHPlayer.h"
#include "Player/Controller/EHPlayerController.h"
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

    Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
    Floor->SetupAttachment(Car);

    ElevatorLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("ElevatorLight"));
    ElevatorLight->SetupAttachment(Car);

    Elevator_AC = CreateDefaultSubobject<UAudioComponent>(TEXT("Elevator AC"));
    Elevator_AC->SetupAttachment(Car);

    Door_AC = CreateDefaultSubobject<UAudioComponent>(TEXT("Door AC"));
    Door_AC->SetupAttachment(Car);

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
    bIsDoorMoving = false;
    ReferencePosition = this->GetActorLocation();
    ReferenceRotation = this->GetActorRotation();
    StartPos += ReferencePosition;
    MapPos += ReferencePosition;
    EndPos += ReferencePosition;
    FOnTimelineFloat UpdateFunc;
    FOnTimelineEvent FinishedFunc;

    auto* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
    Sub->OnAnomalySpawned.AddDynamic(this, &ThisClass::StartElevator);
    Sub->RegisterElevator(this);

    UpdateFunc.BindUFunction(this, FName("OnDoorTimelineUpdate"));
    DoorTimeline->AddInterpFloat(DoorCurve, UpdateFunc);
    FinishedFunc.BindUFunction(this, FName("OnDoorTimelineFinished"));
    DoorTimeline->SetTimelineFinishedFunc(FinishedFunc);
    
    if(InsideButton.Get())
    {
        InsideButton->OnButtonPressed.AddDynamic(this, &AElevator::OnButtonClicked);
    }
    if (EntranceButton.Get())
    {
        EntranceButton->OnButtonPressed.AddDynamic(this, &AElevator::OnButtonClicked);
    }
}

#pragma endregion

#pragma region MovementSettings

void AElevator::MoveDoors(bool bWillOpen)
{
    if (bIsDoorMoving)
    {
        return;
    }

    bIsDoorOpened = bWillOpen;
    Door_AC->Activate(true);
    Elevator_AC->Stop();
    Door_AC->Play();

    if (bWillOpen)
    {
        DoorTimeline->Play();
    }
    else
    {
        DoorTimeline->Reverse();
    }
}

void AElevator::OnDoorTimelineUpdate(float Alpha)
{
    bIsDoorMoving = true;
    LeftDoor->SetRelativeLocation(FMath::Lerp(LeftDoorClosed, LeftDoorOpenPos, Alpha));
    RightDoor->SetRelativeLocation(FMath::Lerp(RightDoorClosed, RightDoorOpenPos, Alpha));
    TriggerBlockBox->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
    TriggerBlockBox->SetBoxExtent(BlockBoxActiveExtent);
}

void AElevator::OnDoorTimelineFinished()
{
    bIsDoorMoving = false;
    Door_AC->Stop();
    TriggerBlockBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    TriggerBlockBox->SetBoxExtent(FVector(0, 0, 0));
}

void AElevator::MoveElevator(FVector Start, FVector End, bool bIsStart)
{
    RootComponent->SetRelativeLocation(Start);
    Elevator_AC->Activate(true);
    Elevator_AC->Play();

    FLatentActionInfo LatentInfo;
    LatentInfo.CallbackTarget = this;
    LatentInfo.UUID = __LINE__;
    LatentInfo.Linkage = 0;
    
    UKismetSystemLibrary::MoveComponentTo(RootComponent, End, ReferenceRotation, false, false, ElevatorMoveDuration, false, EMoveComponentAction::Move, LatentInfo);

    FTimerHandle StartDelayHandle;
    GetWorld()->GetTimerManager().SetTimer(StartDelayHandle, FTimerDelegate::CreateWeakLambda(this, [this, bIsStart]()
        {
            if (bIsStart)
            {
                MoveDoors(true);
            }
            else
            {
                NotifySubsystem();
            }
        }), ElevatorMoveDuration + 0.1f, false);
}

#pragma endregion

#pragma region Button

void AElevator::OnButtonClicked(bool bIsOpening)
{
    ElevatorLight->SetIntensity(LightOnIntensity);
    MoveDoors(bIsOpening);
    if (!bIsOpening)
    {
        FTimerHandle DoorHandle;
        GetWorld()->GetTimerManager().SetTimer(DoorHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
            {
                MoveElevator(MapPos, EndPos, false);
            }), DoorDuration, false);
    }
}

#pragma endregion

#pragma region Subsystem

void AElevator::NotifySubsystem()
{
    auto* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    auto* PC = Player->GetController();
    UCharacterMovementComponent* CMC = Player->GetCharacterMovement();

    FTransform AnchorWorldTransform = TeleportAnchor->GetComponentTransform();
    FVector WorldLocation = Player->GetActorLocation();

    FVector LocalLocation = AnchorWorldTransform.InverseTransformPosition(WorldLocation);
    FRotator Rotation = PC->GetControlRotation();

    FVector PreVelocity = CMC->Velocity;
    float HorizontalSpeed = FVector(PreVelocity.X, PreVelocity.Y, 0.f).Size();
    FVector PreForward = Player->GetActorForwardVector();

    if (UGameSystem* Sub = GetGameInstance()->GetSubsystem<UGameSystem>())
    {
        Sub->SetIsElevatorNormal(this->bIsNormalElevator);
        Sub->SetPlayerVelocity(HorizontalSpeed);
        Sub->TryInteractSolveVerdict();
        Sub->SetPlayerinElevatorTransform(LocalLocation, Rotation, this->GetActorRotation());
        Sub->ApplyVerdict();
    }
}

void AElevator::StartElevator()
{
    TriggerBlockBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    TriggerBlockBox->SetBoxExtent(FVector(0, 0, 0));

    auto* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
    if (Sub->IsTargetElevator(this))
    {
        ElevatorLight->SetIntensity(LightOnIntensity);
        RootComponent->SetRelativeLocation(StartPos);
        auto* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
        auto* PC = Player->GetController();
        UCharacterMovementComponent* CMC = Player->GetCharacterMovement();
        
        FVector SavedRelative = Sub->GetPlayerinElevatorLocation();
        FRotator SavedRotation = Sub->GetPlayerinElevatorRotation();
        SavedRotation -= Sub->GetElevatorOffset() - this->GetActorRotation();
        FTransform AnchorWorldTransform = TeleportAnchor->GetComponentTransform();
        FVector TargetWorldLocation = AnchorWorldTransform.TransformPosition(SavedRelative);
        Player->SetActorLocation(TargetWorldLocation, false, nullptr, ETeleportType::TeleportPhysics);
        Player->SetActorRotation(SavedRotation);
        PC->SetControlRotation(SavedRotation);

        Player->SetBase(nullptr);
        FVector NewForward = Player->GetActorForwardVector();
        CMC->Velocity = FVector(NewForward.X, NewForward.Y, 0.0f) * Sub->GetPlayerVelocity();
        CMC->SetMovementMode(MOVE_Falling);
        FTimerHandle ReEnableHandle;
        GetWorld()->GetTimerManager().SetTimer(ReEnableHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
            {
                MoveElevator(StartPos, MapPos, true);
            }), 0.05f, false);
    }
    else
    {
        this->Exterior_Structure->SetRelativeLocation(MapPos);
        LeftDoor->SetRelativeLocation(LeftDoorClosed);
        RightDoor->SetRelativeLocation(RightDoorClosed);
        bIsDoorOpened = false;
        bIsDoorMoving = false;
        ElevatorLight->SetIntensity(LightOffIntensity);
    }
}

#pragma endregion

#pragma region ElevatorFloor

void AElevator::DisableElevatorFloor()
{
    Floor->SetVisibility(false);
    Floor->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

#pragma endregion