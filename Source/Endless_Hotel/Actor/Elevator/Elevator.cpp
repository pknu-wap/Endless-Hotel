// Copyright by 2025-2 WAP Game 2 team

#include "Elevator.h"
#include "Player/Controller/EHPlayerController.h"
#include "Actor/Elevator/Elevator_Button.h"
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
#include <GameFramework/SpringArmComponent.h>

DEFINE_LOG_CATEGORY_STATIC(LogElevator, Log, All);

FElevatorDelegate AElevator::ElevatorDelegate;

#pragma region Base

AElevator::AElevator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ElevatorSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(ElevatorSceneRoot);

	Car = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Car"));
	Car->SetupAttachment(RootComponent);

	Exterior_Structure = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Exterior_Structure"));
	Exterior_Structure->SetupAttachment(Car);

	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
	LeftDoor->SetupAttachment(Car);

	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));
	RightDoor->SetupAttachment(Car);

	RightGlass = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightGlass"));
	RightGlass->SetupAttachment(RightDoor);

	LeftGlass = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftGlass"));
	LeftGlass->SetupAttachment(LeftDoor);

	Entrance = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Entrance"));
	Entrance->SetupAttachment(ElevatorSceneRoot);

	ElevatorLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("ElevatorLight"));
	ElevatorLight->SetupAttachment(Car);

	AC = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AC->SetupAttachment(RootComponent);

	InsideTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("InsideTrigger"));
	InsideTrigger->SetupAttachment(Car);
	InsideTrigger->SetBoxExtent(FVector(80.f, 80.0f, 120.0f));
	InsideTrigger->SetCollisionProfileName(TEXT("Trigger"));
	InsideTrigger->SetGenerateOverlapEvents(true);
	InsideTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	InsideTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	LeftDoor->SetUsingAbsoluteLocation(false);
	RightDoor->SetUsingAbsoluteLocation(false);

	DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeline"));

	StickerPannel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Elevator_Sticker"));
	StickerPannel->SetupAttachment(Entrance);
}

void AElevator::BeginPlay()
{
	Super::BeginPlay();
	check(LeftDoor && RightDoor && DoorTimeline && InsideTrigger);

	LeftDoorClosed = LeftDoor->GetRelativeLocation();
	RightDoorClosed = RightDoor->GetRelativeLocation();

	const FVector LOff = bSlideOnX ? FVector(-DoorGap, 0, 0) : FVector(0, -DoorGap, 0);
	const FVector ROff = bSlideOnX ? FVector(DoorGap, 0, 0) : FVector(0, DoorGap, 0);

	LeftDoorOpenPos = LeftDoorClosed + LOff;
	RightDoorOpenPos = RightDoorClosed + ROff;

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

	InsideTrigger->OnComponentBeginOverlap.AddDynamic(this, &AElevator::OnInsideBegin);
	InsideTrigger->OnComponentEndOverlap.AddDynamic(this, &AElevator::OnInsideEnd);

	UAnomalyProgressSubSystem* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
	if (Sub->bPassed)
	{
		if (bMapStartElevator)
		{
			ElevatorLight->SetIntensity(LightOnIntensity);
			ElevatorMove(StartPos, MapPos, true);
		}
	}
	else
	{
		SetActorLocation(MapPos);
	}
	SetPlayerInputEnabled(true);
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
	
	FTimerHandle RotateTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(RotateTimerHandle, this, &AElevator::RotatePlayer, 0.1f, false);

	FTimerHandle TakeTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TakeTimerHandle, this, &AElevator::TakePlayer, 0.5f, false);

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
	AC->Sound = Sound_ElevatorMove;
	AC->Play();
	SetActorLocation(Start);
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(RootComponent, End, GetActorRotation(),
		false, false, ElevatorMoveDuration, false, EMoveComponentAction::Type::Move, LatentInfo);

	if (bIsStart)
	{
		bIsPlayerInside = true;
		FTimerHandle MoveHandle;
		GetWorld()->GetTimerManager().SetTimer(
			MoveHandle,
			FTimerDelegate::CreateWeakLambda(this, [this, MoveHandle]() mutable
				{
					MoveDoors(true);
					GetWorld()->GetTimerManager().ClearTimer(MoveHandle);
					bIsPlayerInside = false;
				}),
			ElevatorMoveDuration,
			false
		);
	}
	else
	{
		ElevatorDelegate.Broadcast(false);
	}
}

#pragma endregion

#pragma region SubSystem

void AElevator::NotifySubsystemElevatorChoice()
{
	if (bChoiceSentThisRide) return;
	UAnomalyProgressSubSystem* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
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

	GetWorld()->GetTimerManager().SetTimer(RotateHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			SmoothRotate(RotateAngle);
		}), 0.01f, true);
}

void AElevator::SmoothRotate(FRotator TargetRotation)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AEHPlayerController* PC = Cast<AEHPlayerController>(Player->GetController());
	FRotator CurrentRotation = PC->GetControlRotation();
	FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, 0.01f, 5.0f);
	PC->SetControlRotation(SmoothRotation);

	if (SmoothRotation.Equals(TargetRotation, 0.01f))
	{
		SmoothRotation = TargetRotation;
		PC->SetControlRotation(SmoothRotation);
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
	SetPlayerInputEnabled(false);
}

#pragma endregion