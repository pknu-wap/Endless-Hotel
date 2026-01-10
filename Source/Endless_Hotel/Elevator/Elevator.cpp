// Copyright by 2025-2 WAP Game 2 team

#include "Elevator.h"
#include "Player/Controller/EHPlayerController.h"
#include "Elevator/Elevator_Button.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"
#include "Player/Character/EHPlayer.h"
#include <Components/StaticMeshComponent.h>
#include <Components/PointLightComponent.h>
#include <Components/TimelineComponent.h>
#include <Curves/CurveFloat.h>
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>
#include <Components/AudioComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/BoxComponent.h>
#include <Camera/CameraComponent.h>

DEFINE_LOG_CATEGORY_STATIC(LogElevator, Log, All);

FElevatorDelegate AElevator::ElevatorDelegate;

#pragma region Base

AElevator::AElevator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// 1) Root
	ElevatorSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(ElevatorSceneRoot);

	// 2) Frame
	Car = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Car"));
	Car->SetupAttachment(RootComponent);

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

	// 5) Button
	ElevatorButton = CreateDefaultSubobject<AElevator_Button>(TEXT("ElevatorButton"));

	// 6) Light
	ElevatorLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("ElevatorLight"));
	ElevatorLight->SetupAttachment(Car);

	// 7) Sound
	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AC->SetupAttachment(RootComponent);

	// 8) Trigger
	InsideTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("InsideTrigger"));
	InsideTrigger->SetupAttachment(Car);
	InsideTrigger->SetBoxExtent(FVector(80.f, 80.0f, 120.0f));
	InsideTrigger->SetCollisionProfileName(TEXT("Trigger"));
	InsideTrigger->SetGenerateOverlapEvents(true);
	InsideTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	InsideTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// 10) Location Settings
	LeftDoor->SetUsingAbsoluteLocation(false);
	RightDoor->SetUsingAbsoluteLocation(false);

	// 11) Timeline
	DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeline"));
}

void AElevator::BeginPlay()
{
	Super::BeginPlay();
	check(LeftDoor && RightDoor && DoorTimeline && InsideTrigger);

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
	InsideTrigger->OnComponentBeginOverlap.AddDynamic(this, &AElevator::OnInsideBegin);
	InsideTrigger->OnComponentEndOverlap.AddDynamic(this, &AElevator::OnInsideEnd);

	// 5) Buttons
	ElevatorButton->SetOwnerElevator(this);

	// 6) MoveElevator
	UAnomalyProgressSubSystem* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
	if (Sub->bPassed)
	{
		if (!bIsNormalElevator)
		{
			SetPlayerInputEnabled(false);
			ElevatorLight->SetIntensity(LightOnIntensity);
			ElevatorMove(StartPos, MapPos, true);
		}
	}
	else
	{
		SetActorLocation(MapPos);
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
	bIsDoorMoving = false;
	SetPlayerInputEnabled(true);
}

#pragma endregion

#pragma region DoorMovement

void AElevator::MoveDoors(bool bIsOpening)
{
	if (!DoorTimeline || !DoorCurve) return;
	if (bIsDoorMoving && bIsOpening == bIsDoorOpened) return;

	DoorTimeline->Stop();
	DoorTimeline->SetPlayRate(1.f / FMath::Max(0.01f, DoorDuration));
	AC->Sound = Sound_DoorMove;
	AC->Play();

	if (bIsOpening)
	{
		bIsDoorOpened = true;
		SetPlayerInputEnabled(false);
		DoorTimeline->PlayFromStart();
	}
	else
	{
		bIsDoorOpened = false;
		DoorTimeline->ReverseFromEnd();
	}

	bIsDoorOpened = bIsOpening;
}

void AElevator::TryCloseDoorAfterDelay()
{
	if (bIsPlayerInside) return;
	if(bIsDoorOpened && !bIsDoorMoving) MoveDoors(false);
}

#pragma endregion

#pragma region Trigger

void AElevator::OnInsideBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEHPlayer* Player = Cast<AEHPlayer>(OtherActor);
	if (!Player) return;
	if (bIsPlayerInside) return;
	bIsPlayerInside = true;
	FTimerHandle MovePlayerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		MovePlayerHandle,
		FTimerDelegate::CreateWeakLambda(this, [this, &MovePlayerHandle]()
			{
				TakePlayer();
				GetWorld()->GetTimerManager().ClearTimer(MovePlayerHandle);
			}),
		0.5f,
		false
	);
	GetWorld()->GetTimerManager().SetTimer(
		MovePlayerHandle,
		FTimerDelegate::CreateWeakLambda(this, [this, &MovePlayerHandle]()
			{
				RotatePlayer();
				GetWorld()->GetTimerManager().ClearTimer(MovePlayerHandle);
			}),
		0.1f,
		false
	);
	MoveDoors(false);
	ElevatorLight->SetIntensity(LightOnIntensity);
	if (!bChoiceSentThisRide)
		NotifySubsystemElevatorChoice();
}

void AElevator::OnInsideEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AEHPlayer* Player = Cast<AEHPlayer>(OtherActor);
	if (!Player) return;
	if (!bIsPlayerInside && bIsDoorOpened)
	{
		GetWorld()->GetTimerManager().SetTimer(
			DoorCloseTimerHandle,
			this,
			&AElevator::TryCloseDoorAfterDelay,
			DoorDuration,
			false
		);
		if (!bIsPlayerInside) ElevatorLight->SetIntensity(LightOffIntensity);
	}
}

#pragma endregion

#pragma region ElevatorMovement

void AElevator::CallElevator()
{
	MoveDoors(true);
}

void AElevator::ElevatorMove(FVector Start, FVector End, bool bIsStart)
{
	SetPlayerInputEnabled(false);
	AC->Sound = Sound_ElevatorMove;
	AC->Play();
	SetActorLocation(Start);
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(RootComponent, End, GetActorRotation(),
		false, false, ElevatorMoveDuration, false, EMoveComponentAction::Type::Move, LatentInfo);

	if (bIsStart)
	{
		FTimerHandle MoveHandle;
		GetWorld()->GetTimerManager().SetTimer(
			MoveHandle,
			FTimerDelegate::CreateWeakLambda(this, [this, MoveHandle]() mutable
				{
					MoveDoors(true);
					SetPlayerInputEnabled(true);
					GetWorld()->GetTimerManager().ClearTimer(MoveHandle);
				}),
			ElevatorMoveDuration,
			false
		);
	}
	else
	{
		ElevatorDelegate.Broadcast(bIsStart);
	}
}

#pragma endregion

#pragma region SubSystem

void AElevator::NotifySubsystemElevatorChoice()
{
	if (bChoiceSentThisRide) return;
	UAnomalyProgressSubSystem* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
	SetPlayerInputEnabled(false);
	FTimerHandle WaitHandle;
	FTimerHandle MoveHandle;
	GetWorld()->GetTimerManager().SetTimer(MoveHandle, FTimerDelegate::CreateWeakLambda(this, [this, Sub, MoveHandle]() mutable
		{
			ElevatorMove(MapPos, EndPos, false);
			GetWorld()->GetTimerManager().ClearTimer(MoveHandle);
		}), DoorDuration, false);

	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateWeakLambda(this, [this, Sub]()
		{
			Sub->SetIsElevatorNormal(bIsNormalElevator);
			Sub->TryInteractSolveVerdict();
			Sub->ApplyVerdict();
			bChoiceSentThisRide = true;
		}), DoorDuration + ElevatorMoveDuration, false);
}

#pragma endregion

#pragma region PlayerMoveControl

void AElevator::SetPlayerInputEnabled(bool bEnable)
{
	if (ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		if (AEHPlayerController* PC = Cast<AEHPlayerController>(Player->GetController()))
		{
			PC->bIsCameraFixed = !bEnable;
			PC->bCanMove = bEnable;
			PC->bCanCrouch = bEnable;
		}
	}
}

void AElevator::RotatePlayer()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FRotator LookRotation = FRotator(0.f, RotateAngle, 0.f);
	Player->bUseControllerRotationYaw = false;
	auto* MoveComp = Player->GetCharacterMovement();
	MoveComp->StopMovementImmediately();
	MoveComp->DisableMovement();
	GetWorld()->GetTimerManager().SetTimer(RotateHandle, FTimerDelegate::CreateWeakLambda(this, [this, LookRotation]()
		{
			SmoothRotate(LookRotation);
		}), 0.01f, true);
	TakePlayer();
	MoveComp->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AElevator::SmoothRotate(FRotator TargetRotation)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FRotator CurrentRotation = FRotator(0, Player->GetActorRotation().Yaw, 0);
	FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, 0.01f, 5.0f);
	UCameraComponent* PlayerCamera = Player->FindComponentByClass<UCameraComponent>();
	Player->SetActorRotation(SmoothRotation);
	PlayerCamera->SetRelativeRotation(FRotator(-3, -0.000768, -0.000162));
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetControlRotation(SmoothRotation);

	if (SmoothRotation.Equals(TargetRotation, 0.01f))
	{
		SmoothRotation = TargetRotation;
		Player->SetActorRotation(SmoothRotation);
		TakePlayer();
		GetWorld()->GetTimerManager().ClearTimer(RotateHandle);
	}
}

void AElevator::TakePlayer()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector3d FixedLocation = Player->GetActorLocation();
	FixedLocation.X = PlayerLocationInElevator.X;
	FixedLocation.Y = PlayerLocationInElevator.Y;
	Player->SetActorLocation(FixedLocation);
}

#pragma endregion