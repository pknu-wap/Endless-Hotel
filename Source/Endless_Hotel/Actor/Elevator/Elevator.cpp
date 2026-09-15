// Copyright by 2025-2 WAP Game 2 team

#include "Elevator.h"
#include "Actor/Elevator/Elevator_Button.h"
#include "Anomaly/Event/Anomaly_Event.h"
#include "Player/Character/EHPlayer.h"
#include "Player/Controller/EHPlayerController.h"
#include "Actor/Elevator/Elevator_Wall.h"
#include "Actor/Elevator/Elevator_Entrance.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
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
    bIsDoorMoving = false;
    FOnTimelineFloat UpdateFunc;
    FOnTimelineEvent FinishedFunc;

    auto* Sub = GetGameInstance()->GetSubsystem<UElevatorManagerSubsystem>();
    Sub->RegisterElevator(this);

    UpdateFunc.BindUFunction(this, FName("OnDoorTimelineUpdate"));
    DoorTimeline->AddInterpFloat(DoorCurve, UpdateFunc);
    FinishedFunc.BindUFunction(this, FName("OnDoorTimelineFinished"));
    DoorTimeline->SetTimelineFinishedFunc(FinishedFunc);
    
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

void AElevator::MoveDoors(bool bWillOpen)
{
    if (Move_AC->IsPlaying())
    {
        Move_AC->Stop();
    }
    bIsDoorOpened = bWillOpen;
    Door_AC->Activate(true);
    Door_AC->Play();
    DoorTimeline->Stop();

    if (bWillOpen)
    {
        DoorTimeline->PlayFromStart();
        LeftDoor->SetLightingChannels(true, true, false);
        RightDoor->SetLightingChannels(true, true, false);
    }
    else
    {
        DoorTimeline->ReverseFromEnd();
    }
}

void AElevator::OnDoorTimelineUpdate(float Alpha)
{
    bIsDoorMoving = true;
    LeftDoor->SetRelativeLocation(FMath::Lerp(LeftDoorClosed, LeftDoorOpenPos, Alpha));
    RightDoor->SetRelativeLocation(FMath::Lerp(RightDoorClosed, RightDoorOpenPos, Alpha));
    SetActiveBlockBox(true);
}

void AElevator::OnDoorTimelineFinished()
{
    bIsDoorMoving = false;
    Door_AC->Stop();
    SetActiveBlockBox(false);
}

void AElevator::MoveElevator(FVector Start, FVector End, bool bIsStart)
{
    RootComponent->SetRelativeLocation(Start);
    LeftDoor->SetLightingChannels(false, true, false);
    RightDoor->SetLightingChannels(false, true, false);
    auto* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
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
    auto* VerdictSub = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();
    auto* ElevatorSub = GetGameInstance()->GetSubsystem<UElevatorManagerSubsystem>();

    VerdictSub->SetIsElevatorNormal(this->bIsNormalElevator);
    ElevatorSub->SetPlayerVelocity(HorizontalSpeed);
    VerdictSub->TryInteractSolveVerdict();
    ElevatorSub->SetPlayerinElevatorTransform(LocalLocation, Rotation, this->GetActorRotation());
    VerdictSub->ApplyVerdict();
}

void AElevator::StartElevator()
{
    if (ElevatorUnderWall.IsValid())
    {
        ElevatorUnderWall->ResetWall();
    }
    if (ElevatorOverWall.IsValid())
    {
        ElevatorOverWall->ResetWall();
    }
    DoorTimeline->Stop();
    bIsDoorOpened = false;
    bIsDoorMoving = false;
    LeftDoor->SetRelativeLocation(LeftDoorClosed);
    RightDoor->SetRelativeLocation(RightDoorClosed);
    LeftDoor->SetLightingChannels(true, true, false);
    RightDoor->SetLightingChannels(true, true, false);

    Floor->SetVisibility(true);
    Floor->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    auto* ElevatorSub = GetGameInstance()->GetSubsystem<UElevatorManagerSubsystem>();
    if (ElevatorSub->IsTargetElevator(this))
    {
        if(LinkedEntrance.IsValid())
        {
            LinkedEntrance->SetTriggerActive();
        }
        if (InsideButton.IsValid())
        {
            InsideButton->CanPressButton(false);
        }
        LeftDoor->SetLightingChannels(false, true, false);
        RightDoor->SetLightingChannels(false, true, false);
        SetLightOn(true);
        RootComponent->SetRelativeLocation(StandardPos + StartPos);
        auto* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
        AEHPlayerController* PC = Cast<AEHPlayerController>(Player->GetController());
        UCharacterMovementComponent* CMC = Player->GetCharacterMovement();
        
        Exterior_Structure->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        Car->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        FVector SavedRelative = ElevatorSub->GetPlayerinElevatorLocation();
        FRotator SavedRotation = ElevatorSub->GetPlayerinElevatorRotation();
        SavedRotation -= ElevatorSub->GetElevatorOffset() - this->GetActorRotation();
        FRotator ForPlayerSavedRotation = FRotator(0, SavedRotation.Yaw, SavedRotation.Roll);
        FTransform AnchorWorldTransform = TeleportAnchor->GetComponentTransform();
        FVector TargetWorldLocation = AnchorWorldTransform.TransformPosition(SavedRelative);
        Player->SetActorLocation(TargetWorldLocation, false, nullptr, ETeleportType::TeleportPhysics);
        Player->SetActorRotation(ForPlayerSavedRotation);
        PC->SetControlRotation(SavedRotation);
        PC->PlayerCameraManager->SetGameCameraCutThisFrame();

        if (ElevatorOverWall.IsValid())
        {
            ElevatorOverWall->MoveWall(ElevatorMoveDuration);
        }

        Player->SetBase(nullptr);
        Player->SetActorEnableCollision(true);
        FVector NewForward = Player->GetActorForwardVector();
        CMC->Velocity = FVector(NewForward.X, NewForward.Y, 0.0f) * ElevatorSub->GetPlayerVelocity();

        FTimerHandle RestoreHandle;
        GetWorld()->GetTimerManager().SetTimer(RestoreHandle, FTimerDelegate::CreateWeakLambda(this, [this]
            {
                Exterior_Structure->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
                Car->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
            }), 0.05f, false);

        CMC->SetMovementMode(MOVE_Falling);
        FTimerHandle ReEnableHandle;
        GetWorld()->GetTimerManager().SetTimer(ReEnableHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
            {
                MoveElevator(StandardPos + StartPos, StandardPos + MapPos, true);
            }), ElevatorMoveDuration, false);
    }
    else
    {
        if(LinkedEntrance.IsValid())
        {
            LinkedEntrance->ResetTrigger();
        }
        if (InsideButton.IsValid())
        {
            InsideButton->CanPressButton(true);
        }
        this->Exterior_Structure->SetRelativeLocation(StandardPos + MapPos);
        LeftDoor->SetRelativeLocation(LeftDoorClosed);
        RightDoor->SetRelativeLocation(RightDoorClosed);
        bIsDoorOpened = false;
        bIsDoorMoving = false;
        SetLightOn(false);
    }
}

#pragma endregion

#pragma region Trigger

void AElevator::SetActiveBlockBox(bool bIsActive)
{
    TriggerBlockBox->SetCollisionEnabled(bIsActive ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);
    TriggerBlockBox->SetBoxExtent(bIsActive ? BlockBoxActiveExtent : FVector(0, 0, 0));
}

#pragma endregion

#pragma region Anomaly

void AElevator::DisableElevatorFloor()
{
    Floor->SetVisibility(false);
    Floor->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AElevator::DisableElevator()
{
    RootComponent->SetVisibility(false);
}

#pragma endregion