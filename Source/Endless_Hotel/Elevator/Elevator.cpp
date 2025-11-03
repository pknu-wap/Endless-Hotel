// Copyright by 2025-2 WAP Game 2 team

#include "Elevator.h"
#include "Components/BoxComponent.h"          
#include "Components/StaticMeshComponent.h"   
#include "Components/PointLightComponent.h"   
#include "Components/TimelineComponent.h"     
#include "Components/SceneComponent.h"        
#include "Curves/CurveFloat.h"                
#include "TimerManager.h"
#include "GameFramework/Character.h"          
#include "Engine/CollisionProfile.h"          
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"
#include "WorldCollision.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/EngineTypes.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameSystem/Anomaly/Anomaly_Generator.h"
#include "EngineUtils.h"


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

	// 9) Timeline
	DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeline"));
	MoveTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("MoveTimeline"));

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

	UE_LOG(LogElevator, Log, TEXT("[BeginPlay] Closed L=%s R=%s  Open L=%s R=%s"),
		*LeftDoorClosed.ToString(), *RightDoorClosed.ToString(),
		*LeftDoorOpenPos.ToString(), *RightDoorOpenPos.ToString());

	// 3) Timeline Setup
	if (ensureMsgf(DoorCurve != nullptr, TEXT("DoorCurve is not assigned! Please set a 0->1 CurveFloat.")))
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
	SetActorLocation(StartPoint);

	FOnTimelineFloat MoveUpdate;
	MoveUpdate.BindUFunction(this, FName("OnMoveTimelineUpdate"));

	FOnTimelineEvent MoveFinished;
	MoveFinished.BindUFunction(this, FName("OnMoveTimelineFinished"));

	MoveTimeline->AddInterpFloat(MoveCurve, MoveUpdate);
	MoveTimeline->SetTimelineFinishedFunc(MoveFinished);
	MoveTimeline->SetLooping(false);
	MoveTimeline->SetIgnoreTimeDilation(true);

	if (MoveDuration > 0.f)
	{
		MoveTimeline->SetPlayRate(1.f / MoveDuration);
	}
	
	OrigStartPoint = StartPoint;
	OrigLoopPoint = LoopPoint;
	MovePhase = 0;

	// 4) Delegate Setup
	GetInTrigger->OnComponentBeginOverlap.AddDynamic(this, &AElevator::OnOverlapBegin);
	GetInTrigger->OnComponentEndOverlap.AddDynamic(this, &AElevator::OnOverlapEnd);

	InsideTrigger->OnComponentBeginOverlap.AddDynamic(this, &AElevator::OnInsideBegin);
	InsideTrigger->OnComponentEndOverlap.AddDynamic(this, &AElevator::OnInsideEnd);

	// 5) Anomaly Generator Setup
	for (TActorIterator<AAnomaly_Generator> It(GetWorld()); It; ++It)
	{
		AnomalyGenerator = *It;
		break;
	}
}
#pragma endregion

#pragma region DoorTimeline

void AElevator::OnDoorTimelineUpdate(float Alpha)
{
	// Alpha: 0->1 (Reverse : 1->0)
	const FVector L = FMath::Lerp(LeftDoorClosed, LeftDoorOpenPos, Alpha);
	const FVector R = FMath::Lerp(RightDoorClosed, RightDoorOpenPos, Alpha);

	LeftDoor->SetRelativeLocation(L);
	RightDoor->SetRelativeLocation(R);
}

void AElevator::OnDoorTimelineFinished()
{
	bDoorOpen = bWantOpen;
	SetPlayerInputEnabled(true);

	if (!bDoorOpen && bMoveAfterClosePending)
	{
		bMoveAfterClosePending = false;
		GetWorldTimerManager().ClearTimer(StartMoveTimer);
		
		GetWorldTimerManager().SetTimer(
			StartMoveTimer,
			[this]() {MoveUp();  },
			StartMoveDelay,
			false
		);
	}
}

#pragma endregion

#pragma region MoveTimeline

void AElevator::OnMoveTimelineUpdate(float Alpha)
{
	const FVector NewPos = FMath::Lerp(StartPoint, LoopPoint, Alpha);
	SetActorLocation(NewPos);
}

void AElevator::OnMoveTimelineFinished()
{
	if (MovePhase == 0)
	{
		PerformLoopTeleport();

		MovePhase = 1;
		StartPoint = LoopSpawnPoint;
		LoopPoint = OrigStartPoint;

		if (MoveTimeline)
		{
			MoveTimeline->PlayFromStart();
		}
	}
	else
	{
		bIsMoving = false;
		MovePhase = 0;

		StartPoint = OrigStartPoint;
		LoopPoint = OrigLoopPoint;

		bRideCompleted = true;
		bSpawnSentThisStop = false;
		bChoiceSentThisRide = false;

		GetWorldTimerManager().ClearTimer(AutoOpenTimer);
		GetWorldTimerManager().SetTimer(
			AutoOpenTimer,
			[this]()
			{
				OpenDoors();
			},
			AutoOpenTimeAtReturn, false
		);
	}
}

#pragma endregion

#pragma region DoorMovement

// Open& Close
void AElevator::OpenDoors()
{
	if (!DoorTimeline || !DoorCurve) return;
	if (bDoorOpen) return;

	SetPlayerInputEnabled(false);

	DoorTimeline->Stop();
	bWantOpen = true;
	DoorTimeline->SetPlayRate(1.f / FMath::Max(0.01f, DoorOpenDuration));
	DoorTimeline->PlayFromStart();
}

void AElevator::CloseDoors()
{
	if (!DoorTimeline || !DoorCurve) return;
	if (!bDoorOpen) return;

	SetPlayerInputEnabled(false);

	DoorTimeline->Stop();
	bWantOpen = false;
	DoorTimeline->SetPlayRate(1.f / FMath::Max(0.01f, DoorCloseDuration));
	DoorTimeline->ReverseFromEnd();
}

// Trigger Callbacks
void AElevator::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Player only
	if (OtherActor && OtherActor != this && Cast<ACharacter>(OtherActor))
	{
		if (!(PlayerBPClass && OtherActor->IsA(PlayerBPClass)))
		{
			return;
		}
		OpenDoors();
	}
}

void AElevator::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this && Cast<ACharacter>(OtherActor))
	{
		if (!(PlayerBPClass && OtherActor->IsA(PlayerBPClass)))
		{
			return;
		}
	}
}

#pragma endregion

#pragma region ElevatorMove

// API
void AElevator::MoveUp()
{
	if (!MoveTimeline || !MoveCurve) return;
	bIsMoving = true;
	bRideCompleted = false;
	bSpawnSentThisStop = false;

	MovePhase = 0;
	StartPoint = OrigStartPoint;
	LoopPoint = OrigLoopPoint;

	MoveTimeline->PlayFromStart();
}

void AElevator::MoveDown()
{
	if (!MoveTimeline || !MoveCurve) return;
	bIsMoving = true;
	bRideCompleted = false;
	bSpawnSentThisStop = false;

	MovePhase = 0;
	StartPoint = OrigStartPoint;
	LoopPoint = OrigLoopPoint;

	MoveTimeline->ReverseFromEnd();
}

// Teleport With Player
void AElevator::PerformLoopTeleport()
{
	const FVector Delta = LoopSpawnPoint - LoopPoint;

	const FBoxSphereBounds Bounds = (Car ? Car->Bounds : GetRootComponent()->Bounds);
	const FVector Center = Bounds.Origin;
	const FVector Extents = Bounds.BoxExtent + FVector(30.0f, 30.0f, 30.0f);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjTypes;
	ObjTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	TArray<AActor*> OverlapActors;
	const bool bHit = UKismetSystemLibrary::BoxOverlapActors(
		GetWorld(),
		Center,
		Extents,
		ObjTypes,
		ACharacter::StaticClass(),
		ActorsToIgnore,
		OverlapActors
	);
	AddActorWorldOffset(Delta, false, nullptr, ETeleportType::TeleportPhysics);

	if (bHit && OverlapActors.Num() > 0)
	{
		TSet<ACharacter*> UniqueChars;
		for (AActor* A : OverlapActors)
		{
			if (ACharacter* C = Cast<ACharacter>(A))
			{
				UniqueChars.Add(C);
			}
		}

		for (ACharacter* C : UniqueChars)
		{
			if (!IsValid(C)) continue;

			const FVector NewLoc = C->GetActorLocation() + Delta;
			const FRotator NewRot = C->GetActorRotation();

			const bool bOK = C->TeleportTo(NewLoc, NewRot, false, false);

			if (bOK)
			{
				if (UCharacterMovementComponent* Move = C->GetCharacterMovement())
				{
					Move->StopMovementImmediately();
					Move->Velocity = FVector::ZeroVector;
				}
			}
		}
	}
}

// Trigger Callbacks
void AElevator::OnInsideBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && Cast<ACharacter>(OtherActor))
	{
		if (!(PlayerBPClass && OtherActor->IsA(PlayerBPClass)))
		{
			return;
		}

		if (!bChoiceSentThisRide)
		{
			UE_LOG(LogElevator, Log, TEXT("[IsNormalElevaotr: %d]"), bIsNormalElevator);
			NotifySubsystemElevatorChoice();
		}

		if (bSequenceArmed || bIsMoving) return;
		bSequenceArmed = true;
		bPlayerOnboard = true;

		const bool bWasOpen = bDoorOpen;
		CloseDoors();

		GetWorldTimerManager().ClearTimer(StartMoveTimer);
		if (bWaitDoorCloseBeforMove && bWasOpen && DoorTimeline->IsPlaying())
		{
			bMoveAfterClosePending = true;
		}
		else
		{
			GetWorldTimerManager().SetTimer(
				StartMoveTimer,
				[this]()
				{
					MoveUp();
				},
				StartMoveDelay,
				false
			);
		}
	}
}

void AElevator::OnInsideEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this && Cast<ACharacter>(OtherActor))
	{
		if (!(PlayerBPClass && OtherActor->IsA(PlayerBPClass)))
		{
			return;
		}

		bPlayerOnboard = false;

		if (!bIsMoving)
		{
			if (bRideCompleted && !bSpawnSentThisStop)
			{
				bSpawnSentThisStop = true;
				bRideCompleted = false;
			}

			GetWorldTimerManager().ClearTimer(StartMoveTimer);
			bSequenceArmed = false;
		}

		GetWorldTimerManager().ClearTimer(AutoCloseTimer);
		GetWorldTimerManager().SetTimer(
			AutoCloseTimer,
			[this]()
			{
				CloseDoors();
				bSequenceArmed = false;
			},
			AutoCloseDelayAfterExit,
			false
		);
	}
}

// Player Check Helper
bool AElevator::IsMyPlayer(AActor* Other) const
{
	if (!Other) return false;
	if (PlayerBPClass) return Other->IsA(PlayerBPClass);
	return Cast<ACharacter>(Other) != nullptr;
}

#pragma endregion

#pragma region SubSystem

void AElevator::NotifySubsystemElevatorChoice()
{
	if (bChoiceSentThisRide) return;
	UAnomalyProgressSubSystem* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
	Sub->SetIsElevatorNormal(bIsNormalElevator);
	Sub->ApplyVerdict();
	bChoiceSentThisRide = true;
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
#pragma endregion