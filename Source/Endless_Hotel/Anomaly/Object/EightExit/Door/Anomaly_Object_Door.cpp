// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/EightExit/Door/Anomaly_Object_Door.h"
#include "Player/Controller/EHPlayerController.h"
#include "Component/Interact/InteractComponent.h"
#include <Components/StaticMeshComponent.h>
#include <Components/TimelineComponent.h>
#include <Components/AudioComponent.h>
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>
#include <GameFramework/Character.h>

#pragma region Base

AAnomaly_Object_Door::AAnomaly_Object_Door(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Mesh_Handle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Handle"));
	Mesh_Handle->SetupAttachment(RootComponent);

	Timeline_Door = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_Door"));
	Timeline_Handle = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_Handle"));

	Timeline_Open = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_Open"));
	Timeline_Close = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_Close"));

	AC_Effect = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_Effect"));
	AC_Effect->SetupAttachment(RootComponent);

	AC_Voice = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_Voice"));
	AC_Voice->SetupAttachment(RootComponent);
	
	AC_DoorMove = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_DoorMove"));
	AC_DoorMove->SetupAttachment(RootComponent);
	AC_DoorMove->bAutoActivate = false;

	ExitTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("ExitTrigger"));
	ExitTrigger->SetupAttachment(GetRootComponent());

	ExitTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ExitTrigger->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);

	ExitTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	ExitTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ExitTrigger->SetBoxExtent(FVector(100.f, 100.f, 100.f));
}

void AAnomaly_Object_Door::BeginPlay()
{
	Super::BeginPlay();

	ExitTrigger->OnComponentEndOverlap.AddDynamic(this, &AAnomaly_Object_Door::OnExitTriggerEndOverlap);

	Door_Origin = GetActorLocation();
	Handle_Origin = Mesh_Handle->GetRelativeLocation();

	FOnTimelineFloat Update_Door;
	Update_Door.BindUFunction(this, FName("ShakeDoor"));
	Timeline_Door->AddInterpFloat(Curve_Door, Update_Door);

	FOnTimelineFloat Update_Handle;
	Update_Handle.BindUFunction(this, FName("ShakeHandle"));
	Timeline_Handle->AddInterpFloat(Curve_Handle, Update_Handle);

	if (DoorIndex == 8)
	{
		BaseYaw = Object->GetRelativeRotation().Yaw;

		FOnTimelineFloat OpenUpdate;
		OpenUpdate.BindUFunction(this, FName("UpdateRotateOpen"));
		Timeline_Open->AddInterpFloat(Curve_Open, OpenUpdate);

		FOnTimelineFloat CloseUpdate;
		CloseUpdate.BindUFunction(this, FName("UpdateRotateClose"));
		Timeline_Close->AddInterpFloat(Curve_Close, CloseUpdate);

		FOnTimelineEvent CloseFinished;
		CloseFinished.BindUFunction(this, FName("FinishRotateClose"));
		Timeline_Close->SetTimelineFinishedFunc(CloseFinished);
	}
}

#pragma endregion

#pragma region Shake

void AAnomaly_Object_Door::ShakeDoor(float Value)
{
	FVector Target = Door_Origin;
	Target.X += Value;

	Object->SetWorldLocation(Target);
}

void AAnomaly_Object_Door::ShakeHandle(float Value)
{
	FVector Target = Handle_Origin;
	Target.Y += Value;

	Mesh_Handle->SetRelativeLocation(Target);
}

void AAnomaly_Object_Door::DoorShaking()
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::PlayShake_Handle, DoorIndex, false);
}

void AAnomaly_Object_Door::PlayShake_Handle()
{
	if (!AC_Effect->IsPlaying())
	{
		AC_Effect->Sound = Sound_DoorShake;
		AC_Effect->Play();
	}

	if (!AC_Voice->IsPlaying())
	{
		int32 RandomInt = FMath::RandRange(0, Sounds_Voice.Num() + 4);
		if (RandomInt < Sounds_Voice.Num())
		{
			AC_Voice->Sound = Sounds_Voice[RandomInt];
			AC_Voice->Play();
		}
	}

	Timeline_Handle->PlayFromStart();

	GetWorld()->GetTimerManager().SetTimer(HandleHandle, this, &ThisClass::Timer_Handle, 0.17f, true);
}

void AAnomaly_Object_Door::PlayShake_Door()
{
	Timeline_Door->PlayFromStart();

	GetWorld()->GetTimerManager().SetTimer(DoorHandle, this, &ThisClass::Timer_Door, 0.25f, true);
}

void AAnomaly_Object_Door::Timer_Handle()
{
	Timeline_Handle->PlayFromStart();
	ShakeCount_Handle++;

	if (ShakeCount_Handle >= MaxShakeCount_Handle)
	{
		GetWorld()->GetTimerManager().ClearTimer(HandleHandle);

		ShakeCount_Handle = 0;

		PlayShake_Door();
	}
}

void AAnomaly_Object_Door::Timer_Door()
{
	Timeline_Door->PlayFromStart();
	ShakeCount_Door++;

	if (ShakeCount_Door >= MaxShakeCount_Door)
	{
		GetWorld()->GetTimerManager().ClearTimer(DoorHandle);

		ShakeCount_Door = 0;
	}
}

#pragma endregion

#pragma region Open

void AAnomaly_Object_Door::OpenDoor()
{
	StartRotateOpen();
	PlayOpen_Door();
}

void AAnomaly_Object_Door::StartRotateOpen()
{
	OpenYaw = Object->GetRelativeRotation().Yaw;
	Timeline_Open->PlayFromStart();
}

void AAnomaly_Object_Door::PlayOpen_Door()
{
	AC_DoorMove->SetSound(Sound_DoorOpen);
	AC_DoorMove->Play();
}

#pragma endregion

#pragma region Close

void AAnomaly_Object_Door::CloseDoor()
{
	StartRotateClose();
	PlayClose_Door();
}

void AAnomaly_Object_Door::StartRotateClose()
{
	CloseYaw = Object->GetRelativeRotation().Yaw;
	Timeline_Close->PlayFromStart();
}

void AAnomaly_Object_Door::PlayClose_Door()
{
	AC_DoorMove->SetSound(Sound_DoorClose);
	AC_DoorMove->Play();
}

#pragma endregion

#pragma region Rotate

void AAnomaly_Object_Door::UpdateRotateOpen(float Value)
{
	FRotator Rot = Object->GetRelativeRotation();
	Rot.Yaw = OpenYaw + Value;
	Object->SetRelativeRotation(Rot);
}

void AAnomaly_Object_Door::UpdateRotateClose(float Value)
{
	FRotator Rot = Object->GetRelativeRotation();
	Rot.Yaw = CloseYaw - Value;
	Object->SetRelativeRotation(Rot);
}

void AAnomaly_Object_Door::FinishRotateClose()
{
	FRotator Rot = Object->GetRelativeRotation();
	Rot.Yaw = BaseYaw;
	Object->SetRelativeRotation(Rot);
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_Door::Interact_Implementation(AEHCharacter* Interacter)
{
	FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();

	switch (Info.InteractType)
	{
	case EInteractType::DoorOpen:
		MoveToHandlePlayer();
		break;
	}
}

#pragma endregion

#pragma region FirstDoorOpen

void AAnomaly_Object_Door::MoveToHandlePlayer()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Player) return;

	AEHPlayerController* PC = Cast<AEHPlayerController>(Player->GetController());
	PC->SetPlayerInputAble(false);
	PC->SetIgnoreLookInput(true);

	FTransform WorldTarget = TargetPlayerTransform;

	FVector TargetLocation = WorldTarget.GetLocation();
	FRotator TargetRotation = WorldTarget.Rotator();

	TargetLocation.Z = Player->GetActorLocation().Z;

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("OnMoveCompleted");
	LatentInfo.UUID = __LINE__;
	LatentInfo.Linkage = 0;

	UKismetSystemLibrary::MoveComponentTo(
		Player->GetRootComponent(),
		TargetLocation,
		TargetRotation,
		true, true, 0.5f, false,
		EMoveComponentAction::Move,
		LatentInfo
	);
}

void AAnomaly_Object_Door::OnMoveCompleted()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AEHPlayerController* EHPC = Cast<AEHPlayerController>(Player->GetController());

	EHPC->SetControlRotation(Player->GetActorRotation());
	EHPC->OnFirstDoorOpenStarted();

	FTimerHandle DoorOpenHandle;
	GetWorld()->GetTimerManager().SetTimer(DoorOpenHandle, FTimerDelegate::CreateWeakLambda(this, [this, EHPC, Player]()
		{
			EHPC->OnFirstDoorOpenCompleted();
			OnPushMoveStarted();
		}), 2.0f, false);
}

void AAnomaly_Object_Door::OnPushMoveStarted()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AEHPlayerController* EHPC = Cast<AEHPlayerController>(Player->GetController());

	FVector TargetLocation = PushPlayerTransform.GetLocation();
	FRotator TargetRotation = PushPlayerTransform.Rotator();
	EHPC->SetControlRotation(TargetRotation);

	TargetLocation.Z = Player->GetActorLocation().Z;

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("OnPushMoveCompleted");
	LatentInfo.UUID = __LINE__ + 100;
	LatentInfo.Linkage = 0;

	UKismetSystemLibrary::MoveComponentTo(
		Player->GetRootComponent(),
		TargetLocation,
		TargetRotation,
		true, true, 0.5f, false,
		EMoveComponentAction::Move,
		LatentInfo
	);
}

void AAnomaly_Object_Door::OnPushMoveCompleted()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AEHPlayerController* EHPC = Cast<AEHPlayerController>(Player->GetController());

	EHPC->OnPushDoorStarted();
	DoorRotateStarted();

	FTimerHandle DoorPushHandle;
	GetWorld()->GetTimerManager().SetTimer(DoorPushHandle, FTimerDelegate::CreateWeakLambda(this, [this, EHPC, Player]()
		{
			Player->SetActorLocation(PushPlayerTransform.GetLocation(), false, nullptr, ETeleportType::TeleportPhysics);

			EHPC->OnPushDoorCompleted();
			EHPC->SetIgnoreLookInput(false);
		}), 1.0f, false);
}

void AAnomaly_Object_Door::DoorRotateStarted()
{
	FVector TargetLocation = DoorOpenTransform.GetLocation();
	FRotator TargetRotation = DoorOpenTransform.Rotator();

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("DoorRotateCompleted");
	LatentInfo.UUID = __LINE__ + 200;
	LatentInfo.Linkage = 0;

	UKismetSystemLibrary::MoveComponentTo(
		GetRootComponent(),
		TargetLocation,
		TargetRotation,
		true, true, RotationSpeed, false,
		EMoveComponentAction::Move,
		LatentInfo
	);
}

void AAnomaly_Object_Door::DoorRotateCompleted()
{
	bIsDoorOpened = true;
}

void AAnomaly_Object_Door::OnExitTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (OtherActor == Player && bIsDoorOpened)
	{
		CloseFirstDoor();
	}
}

void AAnomaly_Object_Door::CloseFirstDoor()
{
	bIsDoorOpened = false;

	FVector InitialLocation = DoorInitialTransform.GetLocation();
	FRotator InitialRotation = DoorInitialTransform.Rotator();

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("OnDoorClosed");
	LatentInfo.UUID = __LINE__ + 300;
	LatentInfo.Linkage = 0;

	UKismetSystemLibrary::MoveComponentTo(
		GetRootComponent(),
		InitialLocation,
		InitialRotation,
		true, true, RotationSpeed, false,
		EMoveComponentAction::Move,
		LatentInfo
	);
}
#pragma endregion