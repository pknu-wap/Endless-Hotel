// Copyright by 2025-2 WAP Game 2 team

#include "Elevator.h"
#include "Actor/Elevator/Elevator_Button.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "Player/Character/EHPlayer.h"
#include "Player/Controller/EHPlayerController.h"
#include "Anomaly/Base/Anomaly_Event.h"
#include <Components/StaticMeshComponent.h>
#include <Components/PointLightComponent.h>
#include <Components/TimelineComponent.h>
#include <Components/AudioComponent.h>
#include <Components/BoxComponent.h>
#include <Components/ArrowComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>
#include <GameFramework/Character.h>

FElevatorDelegate AElevator::ElevatorDelegate;

#pragma region Base

AElevator::AElevator(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    Entrance = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Entrance"));
    RootComponent = Entrance;

    StickerPannel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Elevator_Sticker"));
    StickerPannel->SetupAttachment(Entrance);

    Exterior_Structure = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Exterior_Structure"));
    Exterior_Structure->SetupAttachment(RootComponent);

    Car = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Car"));
    Car->SetupAttachment(Exterior_Structure);

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
    CameraRotationTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("CameraRotationTimeline"));

    PlayerAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerAnchor"));
    PlayerAnchor->SetupAttachment(Car);

    PlayerDirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("PlayerDirectionArrow"));
    PlayerDirectionArrow->SetupAttachment(PlayerAnchor);
}

void AElevator::BeginPlay()
{
    Super::BeginPlay();
    bIsDoorMoving = false;

    FOnTimelineFloat UpdateFunc;
    FOnTimelineEvent FinishedFunc;

    UpdateFunc.BindUFunction(this, FName("OnDoorTimelineUpdate"));
    DoorTimeline->AddInterpFloat(DoorCurve, UpdateFunc);
    FinishedFunc.BindUFunction(this, FName("OnDoorTimelineFinished"));
    DoorTimeline->SetTimelineFinishedFunc(FinishedFunc);

    UpdateFunc.BindUFunction(this, FName("OnPlayerRotationUpdate"));
    CameraRotationTimeline->AddInterpFloat(RotationCurve, UpdateFunc);
    FinishedFunc.BindUFunction(this, FName("OnPlayerRotationEnd"));
    CameraRotationTimeline->SetTimelineFinishedFunc(FinishedFunc);

    InsideTrigger->OnComponentBeginOverlap.AddDynamic(this, &AElevator::OnInsideBegin);
    InsideTrigger->OnComponentEndOverlap.AddDynamic(this, &AElevator::OnInsideEnd);
    
    if(AttachedButton)
    {
        AttachedButton->OnButtonPressed.AddDynamic(this, &AElevator::OnButtonClicked);
    }

    FTimerHandle DelayHandle;

    GetWorld()->GetTimerManager().SetTimer(DelayHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
        {
            auto* Sub = GetGameInstance()->GetSubsystem<UGameSystem>();
            if (Sub->CurrentAnomaly->TargetElevatorID == ElevatorID && Sub->Floor < 9)
            {
                MoveElevator(StartPos, MapPos, true);
                ElevatorLight->SetIntensity(LightOnIntensity);
                bIsPlayerInside = true;
            }
            else
            {
                Exterior_Structure->SetRelativeLocation(MapPos);
                bIsPlayerInside = false;
            }
        }), 1, false);
}

#pragma endregion

#pragma region Trigger

void AElevator::OnInsideBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!Cast<AEHPlayer>(OtherActor) || bIsPlayerInside)
    {
        return;
    }
    
    bIsPlayerInside = true;
    TakePlayer();
    SetPlayerInputEnabled(false);
}

void AElevator::OnInsideEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (!Cast<AEHPlayer>(OtherActor) || !bIsPlayerInside)
    {
        return;
    }

    InsideTrigger->SetBoxExtent(FVector(40.0f, 40.0f, 120.0f));
    TriggerBlockBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    bIsPlayerInside = false;
    bIsOpening = false;
    FTimerHandle StartDelayHandle;

    GetWorld()->GetTimerManager().SetTimer(StartDelayHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
        {
            MoveDoors();
            ElevatorLight->SetIntensity(LightOffIntensity);
        }), 2, false);
}

#pragma endregion

#pragma region MovementSettings

void AElevator::MoveDoors()
{
    if (bIsDoorMoving)
    {
        return;
    }

    bIsDoorOpened = bIsOpening;
    Door_AC->Play();
    TriggerBlockBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

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
    bIsDoorMoving = true;
    LeftDoor->SetRelativeLocation(FMath::Lerp(LeftDoorClosed, LeftDoorOpenPos, Alpha));
    RightDoor->SetRelativeLocation(FMath::Lerp(RightDoorClosed, RightDoorOpenPos, Alpha));
}

void AElevator::OnDoorTimelineFinished()
{
    bIsDoorMoving = false;
    SetPlayerInputEnabled(true);
    Door_AC->Stop();

    if (!bIsDoorOpened && bIsPlayerInside)
    {
        MoveElevator(MapPos, EndPos, false);
    }
}

void AElevator::MoveElevator(FVector Start, FVector End, bool bIsStart)
{
    bIsOpening = true;
    SetPlayerInputEnabled(false);
    Exterior_Structure->SetRelativeLocation(Start);
    Elevator_AC->Play();
    
    FLatentActionInfo LatentInfo;
    LatentInfo.ExecutionFunction = FName("MoveDoors");
    LatentInfo.CallbackTarget = this;
    LatentInfo.UUID = __LINE__;
    LatentInfo.Linkage = 0;

    if (bIsStart)
    {
        InsideTrigger->SetBoxExtent(FVector(80.f, 80.0f, 120.0f));
    }
    else
    {
        ElevatorDelegate.Broadcast(false);
        FTimerHandle StartDelayHandle;
        GetWorld()->GetTimerManager().SetTimer(StartDelayHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
            {
                NotifySubsystem();
            }), ElevatorMoveDuration + 1.5f, false);
        ElevatorMoveDuration += 10;
    }

    UKismetSystemLibrary::MoveComponentTo(Exterior_Structure, End, FRotator::ZeroRotator, false, false, ElevatorMoveDuration, false, EMoveComponentAction::Move, LatentInfo);
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

void AElevator::TakePlayer()
{
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    AEHPlayerController* PC = Cast<AEHPlayerController>(Player->GetController());
    FRotator TargetRotation = PlayerAnchor->GetRelativeRotation() + RotateAngle;

    Player->AttachToComponent(PlayerAnchor, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
    Player->bUseControllerRotationYaw = false;
    Player->SetActorRelativeLocation(FVector(0,0,85));

    TargetControlRotation = PlayerAnchor->GetComponentRotation() + RotateAngle;
    CameraRotationTimeline->PlayFromStart();
}

void AElevator::OnPlayerRotationUpdate(float Alpha)
{
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    AEHPlayerController* PC = Cast<AEHPlayerController>(Player->GetController());
    FQuat StartQuat = FQuat(StartControlRotation);
    FQuat TargetQuat = FQuat(TargetControlRotation);
    FQuat ResultQuat = FQuat::Slerp(StartQuat, TargetQuat, Alpha);

    PC->SetControlRotation(ResultQuat.Rotator());
    Player->SetActorRotation(ResultQuat.Rotator());
}

void AElevator::OnPlayerRotationEnd()
{
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    AEHPlayerController* PC = Cast<AEHPlayerController>(Player->GetController());

    PC->SetControlRotation(TargetControlRotation);
    Player->SetActorRotation(TargetControlRotation);
    Player->bUseControllerRotationYaw = true;
    Player->SetActorRelativeLocation(FVector(0, 0, 85));

    bIsOpening = false;
    MoveDoors();
}

#pragma endregion

#pragma region Button

void AElevator::OnButtonClicked()
{
    bIsOpening = true;
    ElevatorLight->SetIntensity(LightOnIntensity);
    TriggerBlockBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    MoveDoors();
}

#pragma endregion

#pragma region Subsystem

void AElevator::NotifySubsystem()
{
    if (UGameSystem* Sub = GetGameInstance()->GetSubsystem<UGameSystem>())
    {
        Sub->SetIsElevatorNormal(bIsNormalElevator);
        Sub->TryInteractSolveVerdict();
        Sub->ApplyVerdict();
    }
}

#pragma endregion