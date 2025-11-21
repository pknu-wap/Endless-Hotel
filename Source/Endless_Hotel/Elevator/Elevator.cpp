// Copyright by 2025-2 WAP Game 2 team

#include "Elevator.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "GameFramework/Character.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogElevator, Log, All);

#pragma region Base

AElevator::AElevator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	// 1) Root
	ElevatorSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(ElevatorSceneRoot);

	// 2) Frame
	Car = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Car"));
	Car->SetupAttachment(ElevatorSceneRoot);

	Exterior_Structure = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Exterior_Structure"));
	Exterior_Structure->SetupAttachment(Car);

	// 3) Door / Glass
	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
	LeftDoor->SetupAttachment(Car);

	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));
	RightDoor->SetupAttachment(Car);

	RightGlass = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightGlass"));
	RightGlass->SetupAttachment(RightDoor);

	LeftGlass = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftGlass"));
	LeftGlass->SetupAttachment(LeftDoor);

	// 4) Entrance
	Entrance = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Entrance"));
	Entrance->SetupAttachment(ElevatorSceneRoot);

	// 5) Buttons
	CallPanel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CallPanel"));
	CallPanel->SetupAttachment(Entrance);

	CallDownButtonRing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CallDownButtonRing"));
	CallDownButtonRing->SetupAttachment(CallPanel);

	CallDownButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CallDownButton"));
	CallDownButton->SetupAttachment(CallDownButtonRing);

	CallUpButtonRing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CallUpButtonRing"));
	CallUpButtonRing->SetupAttachment(CallPanel);

	CallUpButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CallUpButton"));
	CallUpButton->SetupAttachment(CallUpButtonRing);

	// 6) Light
	ElevatorLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("ElevatorLight"));
	ElevatorLight->SetupAttachment(Car);

	// 7) EntranceTrigger
	GetInTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("GetInTrigger"));
	GetInTrigger->SetupAttachment(Entrance);
	GetInTrigger->SetBoxExtent(FVector(120.f, 60.0f, 120.0f));
	GetInTrigger->SetCollisionProfileName(TEXT("Trigger"));
	GetInTrigger->SetGenerateOverlapEvents(true);
	GetInTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetInTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// 8) InsideTrigger
	InsideTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("InsideTrigger"));
	InsideTrigger->SetupAttachment(Car);
	InsideTrigger->SetBoxExtent(FVector(80.f, 80.0f, 120.0f));
	InsideTrigger->SetCollisionProfileName(TEXT("Trigger"));
	InsideTrigger->SetGenerateOverlapEvents(true);
	InsideTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	InsideTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// 9) PresenceTrigger
	PresenceTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("PresenceTrigger"));
	PresenceTrigger->SetupAttachment(Car);
	PresenceTrigger->SetBoxExtent(FVector(100.f, 100.0f, 150.0f));
	PresenceTrigger->SetCollisionProfileName(TEXT("Trigger"));
	PresenceTrigger->SetGenerateOverlapEvents(true);
	PresenceTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	PresenceTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// 9) Timeline
	DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeline"));

	// 10) Mobility Settings
	ElevatorSceneRoot->SetMobility(EComponentMobility::Movable);
	Car->SetMobility(EComponentMobility::Movable);
	LeftDoor->SetMobility(EComponentMobility::Movable);
	RightDoor->SetMobility(EComponentMobility::Movable);
	LeftGlass->SetMobility(EComponentMobility::Movable);
	RightGlass->SetMobility(EComponentMobility::Movable);

	// 11) Location Settings
	LeftDoor->SetUsingAbsoluteLocation(false);
	RightDoor->SetUsingAbsoluteLocation(false);
}

void AElevator::BeginPlay()
{
	Super::BeginPlay();

	check(LeftDoor && RightDoor && DoorTimeline && GetInTrigger && InsideTrigger);

	// 1) Closed Location Save
	LeftDoorClosed = LeftDoor->GetRelativeLocation();
	RightDoorClosed = RightDoor->GetRelativeLocation();

	// 2) Open Location Compute
	const FVector LOff = bSlideOnX ? FVector(-DoorGap, 0, 0) : FVector(0, -DoorGap, 0);
	const FVector ROff = bSlideOnX ? FVector(DoorGap, 0, 0) : FVector(0, DoorGap, 0);

	LeftDoorOpenPos = LeftDoorClosed + LOff;
	RightDoorOpenPos = RightDoorClosed + ROff;

	// 3) Timeline Setup
	if (DoorCurve != nullptr)
	{
		FOnTimelineFloat Update;
		Update.BindUFunction(this, FName("OnDoorTimelineUpdate"));

		FOnTimelineEvent Finished;
		Finished.BindUFunction(this, FName("OnDoorTimelineFinished"));

		DoorTimeline->AddInterpFloat(DoorCurve, Update);
		DoorTimeline->SetTimelineFinishedFunc(Finished);
		DoorTimeline->SetLooping(false);
		DoorTimeline->SetIgnoreTimeDilation(true);
	}

	// 4) Delegate Setup
	GetInTrigger->OnComponentBeginOverlap.AddDynamic(this, &AElevator::OnOverlapBegin);
	InsideTrigger->OnComponentBeginOverlap.AddDynamic(this, &AElevator::OnInsideBegin);
	PresenceTrigger->OnComponentBeginOverlap.AddDynamic(this, &AElevator::OnPresenceBegin);
	PresenceTrigger->OnComponentEndOverlap.AddDynamic(this, &AElevator::OnPresenceEnd);

	// 5) MoveElevator
	if (!bIsNormalElevator)
	{
		ElevatorMove(StartPos, MapPos, true);
		bIsPlayerInside = true;
	}
}
#pragma endregion

#pragma region DoorTimeline

void AElevator::OnDoorTimelineUpdate(float Alpha)
{
	// Alpha: 0->1 (Reverse : 1->0)
	const FVector L = FMath::Lerp(LeftDoorClosed, LeftDoorOpenPos, Alpha);
	const FVector R = FMath::Lerp(RightDoorClosed, RightDoorOpenPos, Alpha);

	bIsDoorMoving = true;
	LeftDoor->SetRelativeLocation(L);
	RightDoor->SetRelativeLocation(R);
}

void AElevator::OnDoorTimelineFinished()
{
	SetPlayerInputEnabled(true);
	bIsDoorMoving = false;
}

#pragma endregion

#pragma region DoorMovement

// Open& Close
void AElevator::MoveDoors(bool bIsOpening)
{

	if (!DoorTimeline || !DoorCurve) return;
	if (bIsDoorMoving) return;

	DoorTimeline->Stop();
	DoorTimeline->SetPlayRate(1.f / FMath::Max(0.01f, DoorDuration));
	if(bIsPlayerInside) SetPlayerInputEnabled(false);

	if (bIsOpening)
	{
		bIsDoorOpened = true;
		DoorTimeline->PlayFromStart();
	}
	else
	{
		bIsDoorOpened = false;
		DoorTimeline->ReverseFromEnd();
	}
}

// Trigger Callbacks
void AElevator::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && Cast<ACharacter>(OtherActor) && !bIsPlayerInside)
	{
		if (!(PlayerBPClass && OtherActor->IsA(PlayerBPClass)) || bIsDoorOpened) return;
		MoveDoors(true);
	}
}

void AElevator::ElevatorMove(FVector Start, FVector End, bool bIsStart)
{
	SetPlayerInputEnabled(false);

	SetActorLocation(Start);
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(RootComponent, End, GetActorRotation(),
		false, false, ElevatorMoveDuration, false, EMoveComponentAction::Type::Move, LatentInfo);

	if(bIsStart)
	{
		FTimerHandle MoveHandle;
		GetWorld()->GetTimerManager().SetTimer(MoveHandle, FTimerDelegate::CreateLambda([&]()
			{
				MoveDoors(true);
				SetPlayerInputEnabled(true);
				GetWorld()->GetTimerManager().ClearTimer(MoveHandle);
			}), ElevatorMoveDuration, false);
	}
}

// Trigger Callbacks
void AElevator::OnInsideBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && Cast<ACharacter>(OtherActor))
	{
		if (!(PlayerBPClass && OtherActor->IsA(PlayerBPClass))) return;

		if (!bChoiceSentThisRide)
			NotifySubsystemElevatorChoice();
	}
}

void AElevator::OnPresenceBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!(OtherActor && PlayerBPClass && OtherActor->IsA(PlayerBPClass))) return;
	bIsPlayerInside = true;
}

void AElevator::OnPresenceEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!(OtherActor && PlayerBPClass && OtherActor->IsA(PlayerBPClass))) return;
	bIsPlayerInside = false;
	MoveDoors(false);
}

#pragma endregion

#pragma region SubSystem

void AElevator::NotifySubsystemElevatorChoice()
{
	if (bChoiceSentThisRide) return;
	UAnomalyProgressSubSystem* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
	RotatePlayer();
	MoveDoors(false);
	SetPlayerInputEnabled(false);
	FTimerHandle WaitHandle;
	FTimerHandle MoveHandle;
	
	GetWorld()->GetTimerManager().SetTimer(MoveHandle, [this, MoveHandle]() mutable
		{
			ElevatorMove(MapPos, EndPos, false);
			GetWorld()->GetTimerManager().ClearTimer(MoveHandle);
		}, DoorDuration, false);

	GetWorld()->GetTimerManager().SetTimer(WaitHandle, [this, Sub, WaitHandle]() mutable
		{
			Sub->SetIsElevatorNormal(bIsNormalElevator);
			Sub->ApplyVerdict();
			bChoiceSentThisRide = true;
			GetWorld()->GetTimerManager().ClearTimer(WaitHandle);
		}, DoorDuration + ElevatorMoveDuration, false);
}

#pragma endregion

#pragma region PlayerMoveControl

void AElevator::SetPlayerInputEnabled(bool bEnable)
{
	if (ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		if (APlayerController* PC = Cast<APlayerController>(Player->GetController()))
		{
			PC->SetIgnoreMoveInput(!bEnable);
			PC->SetIgnoreLookInput(!bEnable);
		}
	}
}

void AElevator::RotatePlayer()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Player->bUseControllerRotationYaw = false;
	FRotator LookRotation = FRotator(0.f, RotateAngle, 0.f);
	FRotator PlayerRotation = Player->GetActorRotation();

	GetWorld()->GetTimerManager().SetTimer(RotateHandle, [this, PlayerRotation, LookRotation]()
		{
			SmoothRotate(PlayerRotation, LookRotation);
		}, 0.01f, true);
}

void AElevator::SmoothRotate(FRotator PlayerRotation, FRotator TargetRotation)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FRotator CurrentRotation = Player->GetActorRotation();
	FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, 0.01f, 5.0f);

	Player->SetActorRotation(SmoothRotation);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetControlRotation(SmoothRotation);

	if (SmoothRotation.Equals(TargetRotation, 0.01f))
	{
		SmoothRotation = TargetRotation;
		GetWorld()->GetTimerManager().ClearTimer(RotateHandle);
	}
}

#pragma endregion