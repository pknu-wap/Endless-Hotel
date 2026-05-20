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
    Entrance = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Entrance"));
    RootComponent = Entrance;
    StickerPannel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Elevator_Sticker"));
    StickerPannel->SetupAttachment(RootComponent);

    Exterior_Structure = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Exterior_Structure"));
    Exterior_Structure->SetupAttachment(RootComponent);

    Car = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Car"));
    Car->SetupAttachment(Exterior_Structure);

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

    InsideTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("InsideTrigger"));
    InsideTrigger->SetupAttachment(Car);
    InsideTrigger->SetBoxExtent(InsideTriggerActiveExtent);
    InsideTrigger->SetCollisionProfileName(TEXT("Trigger"));
    InsideTrigger->SetGenerateOverlapEvents(true);

    TriggerBlockBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBlockBox"));
    TriggerBlockBox->SetBoxExtent(BlockBoxActiveExtent);
    TriggerBlockBox->SetupAttachment(Car);
    InsideTrigger->SetCollisionProfileName(TEXT("TriggerBlockBox"));

    TeleportAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("TeleportAnchor"));
    TeleportAnchor->SetupAttachment(Exterior_Structure);
}

void AElevator::BeginPlay()
{
    Super::BeginPlay();
    bIsDoorMoving = false;

    FOnTimelineFloat UpdateFunc;
    FOnTimelineEvent FinishedFunc;

    auto* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
    Sub->OnAnomalySpawned.AddDynamic(this, &ThisClass::StartElevator);
    Sub->RegisterElevator(this);

    UpdateFunc.BindUFunction(this, FName("OnDoorTimelineUpdate"));
    DoorTimeline->AddInterpFloat(DoorCurve, UpdateFunc);
    FinishedFunc.BindUFunction(this, FName("OnDoorTimelineFinished"));
    DoorTimeline->SetTimelineFinishedFunc(FinishedFunc);

    InsideTrigger->OnComponentBeginOverlap.AddDynamic(this, &AElevator::OnInsideBegin);
    InsideTrigger->OnComponentEndOverlap.AddDynamic(this, &AElevator::OnInsideEnd);
    
    if(AttachedButton)
    {
        AttachedButton->OnButtonPressed.AddDynamic(this, &AElevator::OnButtonClicked);
    }
}

#pragma endregion

#pragma region Trigger

void AElevator::OnInsideBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!Cast<AEHPlayer>(OtherActor) || bIsPlayerAlreadyInside)
    {
        return;
    }
    InsideTrigger->SetBoxExtent(FVector(200.f, 200.0f, 150.0f));
    bIsPlayerAlreadyInside = true;
    MoveDoors(false);
    FTimerHandle MoveDelayHandle;
    GetWorld()->GetTimerManager().SetTimer(MoveDelayHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
        {
            MoveElevator(MapPos, EndPos, false);
        }), DoorDuration, false);
}

void AElevator::OnInsideEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (!Cast<AEHPlayer>(OtherActor) || !bIsPlayerAlreadyInside)
    {
        return;
    }

    InsideTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    InsideTrigger->SetBoxExtent(FVector(0, 0, 0));
    TriggerBlockBox->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
    TriggerBlockBox->SetBoxExtent(BlockBoxActiveExtent);

    bIsPlayerAlreadyInside = false;
    FTimerHandle StartDelayHandle;

    GetWorld()->GetTimerManager().SetTimer(StartDelayHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
        {
            MoveDoors(false);
            ElevatorLight->SetIntensity(LightOffIntensity);
        }), DoorDelay, false);
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
    TriggerBlockBox->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
    TriggerBlockBox->SetBoxExtent(BlockBoxActiveExtent);

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
    Exterior_Structure->SetRelativeLocation(Start);
    Elevator_AC->Activate(true);
    Elevator_AC->Play();

    FLatentActionInfo LatentInfo;
    LatentInfo.CallbackTarget = this;
    LatentInfo.UUID = __LINE__;
    LatentInfo.Linkage = 0;
    
    UKismetSystemLibrary::MoveComponentTo(Exterior_Structure, End, FRotator::ZeroRotator, false, false, ElevatorMoveDuration, false, EMoveComponentAction::Move, LatentInfo);

    GetWorld()->GetTimerManager().SetTimer(MoveHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
        {
            if(bIsPlayerAlreadyInside)
            {
                MoveDoors(true);
            }
        }), ElevatorMoveDuration + 0.1f, false);

    if (!bIsStart)
    {
        FTimerHandle StartDelayHandle;
        GetWorld()->GetTimerManager().SetTimer(StartDelayHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
            {
                NotifySubsystem();
            }), ElevatorMoveDuration, false);
    }
}

#pragma endregion

#pragma region Button

void AElevator::OnButtonClicked()
{
    ElevatorLight->SetIntensity(LightOnIntensity);
    MoveDoors(true);
    TriggerBlockBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    TriggerBlockBox->SetBoxExtent(FVector(0, 0, 0));
    InsideTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    InsideTrigger->SetBoxExtent(InsideTriggerActiveExtent);
}

#pragma endregion

#pragma region Subsystem

void AElevator::NotifySubsystem()
{
    auto* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    auto* PC = Player->GetController();
    UCharacterMovementComponent* CMC = Player->GetCharacterMovement();
    bIsPlayerAlreadyInside = false;

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
    InsideTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBlockBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    TriggerBlockBox->SetBoxExtent(FVector(0, 0, 0));

    auto* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
    if (Sub->IsTargetElevator(this))
    {
        ElevatorLight->SetIntensity(LightOnIntensity);
        Exterior_Structure->SetRelativeLocation(StartPos);
        bIsPlayerAlreadyInside = true;
        auto* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
        auto* PC = Player->GetController();
        UCharacterMovementComponent* CMC = Player->GetCharacterMovement();
        InsideTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        
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
                InsideTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
                MoveElevator(StartPos, MapPos, true);
            }), 0.05f, false);
    }
    else
    {
        InsideTrigger->SetBoxExtent(InsideTriggerActiveExtent);
        this->Exterior_Structure->SetRelativeLocation(MapPos);
        bIsPlayerAlreadyInside = false;
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