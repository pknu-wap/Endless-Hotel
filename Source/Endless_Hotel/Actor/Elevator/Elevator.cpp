#include "Elevator.h"
#include "Actor/Elevator/Elevator_Button.h"
#include "GameSystem/SubSystem/GameSystem.h"
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

FElevatorDelegate AElevator::ElevatorDelegate;

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

    RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));
    RightDoor->SetupAttachment(Car);

    Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
    Floor->SetupAttachment(Car);

    RightGlass = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightGlass"));
    RightGlass->SetupAttachment(RightDoor);

    LeftGlass = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftGlass"));
    LeftGlass->SetupAttachment(LeftDoor);

    Entrance = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Entrance"));
    Entrance->SetupAttachment(RootComponent);

    ElevatorLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("ElevatorLight"));
    ElevatorLight->SetupAttachment(Car);

    Elevator_AC = CreateDefaultSubobject<UAudioComponent>(TEXT("Elevator AC"));
    Elevator_AC->SetupAttachment(Car);

    Door_AC = CreateDefaultSubobject<UAudioComponent>(TEXT("Door AC"));
    Door_AC->SetupAttachment(Car);

    InsideTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("InsideTrigger"));
    InsideTrigger->SetupAttachment(Car);
    InsideTrigger->SetBoxExtent(FVector(80.f, 80.0f, 120.0f));
    InsideTrigger->SetCollisionProfileName(TEXT("Trigger"));
    InsideTrigger->SetGenerateOverlapEvents(true);

    TriggerBlockBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TriggerBlockBox"));
    TriggerBlockBox->SetupAttachment(Car);

    DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeline"));

    StickerPannel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Elevator_Sticker"));
    StickerPannel->SetupAttachment(Entrance);
}

void AElevator::BeginPlay()
{
    Super::BeginPlay();

    bIsDoorOpened = false;
    bIsDoorMoving = false;

    EnableFloor();  // 임시

    if (DoorCurve)
    {
        FOnTimelineFloat UpdateFunc;
        UpdateFunc.BindUFunction(this, FName("OnDoorTimelineUpdate"));
        FOnTimelineEvent FinishedFunc;
        FinishedFunc.BindUFunction(this, FName("OnDoorTimelineFinished"));
        DoorTimeline->AddInterpFloat(DoorCurve, UpdateFunc);
        DoorTimeline->SetTimelineFinishedFunc(FinishedFunc);
    }

    InsideTrigger->OnComponentBeginOverlap.AddDynamic(this, &AElevator::OnInsideBegin);
    InsideTrigger->OnComponentEndOverlap.AddDynamic(this, &AElevator::OnInsideEnd);

    if (AttachedButton)
    {
        AttachedButton->OnButtonPressed.AddDynamic(this, &AElevator::OnButtonClicked);
    }

    UGameSystem* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
    if (Sub && Sub->bPassed && bIsMapStartElevator)
    {
        bIsPlayerInside = true;
        InsideTrigger->SetBoxExtent(FVector(150.0f, 150.0f, 40.0f));
        ElevatorLight->SetIntensity(LightOnIntensity);
        FTimerHandle StartDelayHandle;
        GetWorld()->GetTimerManager().SetTimer(StartDelayHandle, [this]() {
            ElevatorMove(StartPos, MapPos, true);
            }, 0.1f, false);
    }
    else
    {
        SetActorLocation(MapPos);
    }
}

#pragma endregion

#pragma region Trigger

void AElevator::OnInsideBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AEHPlayer* Player = Cast<AEHPlayer>(OtherActor);
    if (!Player || bIsPlayerInside) return;

    bIsPlayerInside = true;
    ElevatorLight->SetIntensity(LightOnIntensity);

    SetPlayerInputEnabled(false);
    RotatePlayer();
    TakePlayer();

    bShouldMoveAfterClose = true;

    GetWorld()->GetTimerManager().ClearTimer(BoardingCloseTimerHandle);

    GetWorld()->GetTimerManager().SetTimer(BoardingCloseTimerHandle, [this]() {
        MoveDoors(false);
        }, 1.0, false);
}

void AElevator::OnInsideEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    AEHPlayer* Player = Cast<AEHPlayer>(OtherActor);
    if (!Player) return;

    Player->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

    InsideTrigger->SetBoxExtent(FVector(80.f, 80.0f, 40.0f));
    TriggerBlockBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    FTimerHandle CloseDelayHandle;
    GetWorld()->GetTimerManager().SetTimer(CloseDelayHandle, [this]() {
        bIsPlayerInside = false;
        if (!bIsPlayerInside && bIsDoorOpened) MoveDoors(false);
        }, 2.0f, false);

    ElevatorLight->SetIntensity(LightOffIntensity);
}

#pragma endregion

#pragma region MovementSettings

void AElevator::MoveDoors(bool bIsOpening)
{
    if (bIsDoorMoving && bIsOpening == bIsDoorOpened) return;

    bIsDoorMoving = true;
    CurrentState = EElevatorState::DoorMoving;
    bIsDoorOpened = bIsOpening;
    
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

    if(InsideTrigger->IsOverlappingActor(Player) && bIsPlayerInside)
    {
        SetPlayerInputEnabled(false);
    }

    float NewPlayRate = 1.0f / FMath::Max(0.01f, DoorDuration);
    DoorTimeline->SetPlayRate(NewPlayRate);

    if (Sound_DoorMove) Door_AC->Play();

    if (bIsOpening)
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
    LeftDoor->SetRelativeLocation(FMath::Lerp(LeftDoorClosed, LeftDoorOpenPos, Alpha));
    RightDoor->SetRelativeLocation(FMath::Lerp(RightDoorClosed, RightDoorOpenPos, Alpha));
}

void AElevator::OnDoorTimelineFinished()
{
    bIsDoorMoving = false;

    if (DoorTimeline->GetPlaybackPosition() <= 0.0f)
    {
        if (bShouldMoveAfterClose)
        {
            bShouldMoveAfterClose = false;
            ExecuteElevatorRide();
        }
        else
        {
            CurrentState = EElevatorState::Idle;
        }
    }
    else
    {
        TriggerBlockBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

        CurrentState = EElevatorState::Idle;
        SetPlayerInputEnabled(true);
    }
}

void AElevator::ExecuteElevatorRide()
{
    ElevatorMove(MapPos, EndPos, false);
}

void AElevator::ElevatorMove(FVector Start, FVector End, bool bIsStart)
{
    CurrentState = EElevatorState::Moving;
    if (Sound_ElevatorMove) Elevator_AC->Play();
    SetPlayerInputEnabled(false);

    SetActorLocation(Start);

    FLatentActionInfo LatentInfo;
    LatentInfo.CallbackTarget = this;
    LatentInfo.UUID = __LINE__;
    LatentInfo.Linkage = 0;

    if (bIsStart)
    {
        bIsPlayerInside = true;
        LatentInfo.ExecutionFunction = FName("OpenDoorAfterMove");
    }
    else
    {
        ElevatorDelegate.Broadcast(false);
        LatentInfo.ExecutionFunction = FName("BroadcastElevatorFinished");
    }

    UKismetSystemLibrary::MoveComponentTo(RootComponent, End, GetActorRotation(), false, false, ElevatorMoveDuration, false, EMoveComponentAction::Move, LatentInfo);
}

void AElevator::OpenDoorAfterMove()
{
    MoveDoors(true);
}

void AElevator::BroadcastElevatorFinished()
{
    NotifySubsystemElevatorChoice();
}

#pragma endregion

#pragma region Player

void AElevator::SetPlayerInputEnabled(bool bEnable)
{
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    AEHPlayerController* PC = Cast<AEHPlayerController>(Player->GetController());

    PC->OnCrouchCompleted();
    PC->SetPlayerInputAble(bEnable);
}

void AElevator::RotatePlayer()
{
    SetPlayerInputEnabled(false);
    GetWorld()->GetTimerManager().SetTimer(RotateHandle, FTimerDelegate::CreateWeakLambda(this, [this]() {
        SmoothRotate(RotateAngle);
        }), 0.01f, true);
}

void AElevator::SmoothRotate(FRotator TargetRotation)
{
    SetPlayerInputEnabled(false);
    if (ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
    {
        if (AEHPlayerController* PC = Cast<AEHPlayerController>(Player->GetController()))
        {
            FRotator CurrentRotation = PC->GetControlRotation();
            FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), 5.0f);
            PC->SetControlRotation(SmoothRotation);

            if (SmoothRotation.Equals(TargetRotation, 0.1f))
            {
                PC->SetControlRotation(TargetRotation);
                GetWorld()->GetTimerManager().ClearTimer(RotateHandle);
            }
        }
    }
}

void AElevator::TakePlayer()
{
    SetPlayerInputEnabled(false);
    if (ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
    {
        Player->AttachToComponent(Car, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
    }
}

#pragma endregion

#pragma region Button

void AElevator::OnButtonClicked()
{
    if (CurrentState == EElevatorState::Idle && !bIsPlayerInside)
    {
        MoveDoors(true);
    }
}

#pragma endregion

#pragma region Subsystem

void AElevator::NotifySubsystemElevatorChoice()
{
    if (UGameSystem* Sub = GetGameInstance()->GetSubsystem<UGameSystem>())
    {
        Sub->SetIsElevatorNormal(bIsNormalElevator);
        Sub->TryInteractSolveVerdict();
        Sub->ApplyVerdict();
        bChoiceSentThisRide = true;
    }
}

#pragma endregion

#pragma region Reset

void AElevator::EnableFloor() // 임시
{
    Floor->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Floor->SetVisibility(true);
}

#pragma endregion


#pragma region Anomaly

void AElevator::DisableFloor()
{
    Floor->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Floor->SetVisibility(false);
}

#pragma endregion
