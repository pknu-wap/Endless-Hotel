// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/EightExit/Door/Anomaly_Object_Door.h"
#include "Player/Controller/EHPlayerController.h"
#include "Player/Character/EHPlayer.h"
#include "Component/Interact/InteractComponent.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "GameSystem/SaveGame/SaveManager.h"
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

	TL_Door = CreateDefaultSubobject<UTimelineComponent>(TEXT("TL_Door"));
	TL_Handle = CreateDefaultSubobject<UTimelineComponent>(TEXT("TL_Handle"));

	Timeline_Open = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_Open"));
	Timeline_Close = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_Close"));

	AC_Shake = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_Shake"));
	AC_Shake->SetupAttachment(RootComponent);

	AC_Voice = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_Voice"));
	AC_Voice->SetupAttachment(RootComponent);

	AC_DoorMove = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_DoorMove"));
	AC_DoorMove->SetupAttachment(RootComponent);
	AC_DoorMove->bAutoActivate = false;
}

void AAnomaly_Object_Door::Reset()
{
	Super::Reset();
	Component_Interact->DeactiveInteract();
	SetLight(false);
}

void AAnomaly_Object_Door::BeginPlay()
{
	Super::BeginPlay();

	BaseYaw = Object->GetRelativeRotation().Yaw;

	FOnTimelineFloat OpenUpdate;
	OpenUpdate.BindUFunction(this, FName("UpdateRotateOpen"));
	Timeline_Open->AddInterpFloat(Curve_Open, OpenUpdate);

	FOnTimelineEvent OpenFinished;
	OpenFinished.BindUFunction(this, FName("FinishRotateOpen"));
	Timeline_Close->SetTimelineFinishedFunc(OpenFinished);

	FOnTimelineFloat CloseUpdate;
	CloseUpdate.BindUFunction(this, FName("UpdateRotateClose"));
	Timeline_Close->AddInterpFloat(Curve_Close, CloseUpdate);

	FOnTimelineEvent CloseFinished;
	CloseFinished.BindUFunction(this, FName("FinishRotateClose"));
	Timeline_Close->SetTimelineFinishedFunc(CloseFinished);
}

#pragma endregion

#pragma region Shake

void AAnomaly_Object_Door::StartShaking()
{
	if (bIsFirstShakeSetting)
	{
		DoorOrigin = Object->GetRelativeLocation();
		HandleOrigin = Mesh_Handle->GetRelativeLocation();

		FOnTimelineFloat Update_Door;
		Update_Door.BindUFunction(this, FName("ShakeDoor"));
		TL_Door->AddInterpFloat(CV_Door, Update_Door);

		FOnTimelineFloat Update_Handle;
		Update_Handle.BindUFunction(this, FName("ShakeHandle"));
		TL_Handle->AddInterpFloat(CV_Handle, Update_Handle);

		FOnTimelineEvent Finish_Door;
		Finish_Door.BindUFunction(this, TEXT("ShakeDoorEnd"));
		TL_Door->SetTimelineFinishedFunc(Finish_Door);

		FOnTimelineEvent Finish_Handle;
		Finish_Handle.BindUFunction(this, TEXT("ShakeHandleEnd"));
		TL_Handle->SetTimelineFinishedFunc(Finish_Handle);

		bIsFirstShakeSetting = false;
	}

	int32 RandInt = FMath::RandRange(1, 5);
	FTimerHandle StartHandle;
	GetWorld()->GetTimerManager().SetTimer(StartHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			AC_Shake->Stop();
			AC_Shake->Play();

			AC_Voice->Stop();
			int32 RandInt = FMath::RandRange(0, SW_Voice.Num() - 1);
			AC_Voice->SetSound(SW_Voice[RandInt]);
			AC_Voice->Play();

			ShakeHandleEnd();
		}), RandInt, false);
}

void AAnomaly_Object_Door::ShakeDoor(float Value)
{
	FVector Forward = Object->GetForwardVector() * Value;

	Object->SetRelativeLocation(DoorOrigin + Forward);
}

void AAnomaly_Object_Door::ShakeHandle(float Value)
{
	FVector Up = Mesh_Handle->GetUpVector() * Value;

	Mesh_Handle->SetRelativeLocation(HandleOrigin + Up);
}

void AAnomaly_Object_Door::ShakeDoorEnd()
{
	if (CurrentDoorShake++ < MaxDoorShake)
	{
		TL_Door->PlayFromStart();
		GetWorld()->GetTimerManager().SetTimer(HandleShakeHandle, this, &ThisClass::ShakeDoorEnd, 0.25f, false);
	}
	else
	{
		TL_Door->Stop();
		StartShaking();
		CurrentDoorShake = 0;
	}
}

void AAnomaly_Object_Door::ShakeHandleEnd()
{
	if (CurrentHandleShake++ < MaxHandleShake)
	{
		TL_Handle->PlayFromStart();
		GetWorld()->GetTimerManager().SetTimer(HandleShakeHandle, this, &ThisClass::ShakeHandleEnd, 0.17f, false);
	}
	else
	{
		TL_Handle->Stop();
		TL_Door->PlayFromStart();
		CurrentHandleShake = 0;
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

void AAnomaly_Object_Door::PlayHandleTwistSound()
{
	AC_DoorMove->SetSound(Sound_HandleTwist);
	AC_DoorMove->Play();
}

void AAnomaly_Object_Door::Interact_Implementation(AEHCharacter* Interacter)
{
	if (!USaveManager::LoadData_Progression().bReadManual)
	{
		Component_Interact->RestoreInteract();
		return;
	}

	FSaveData_Progression Data = USaveManager::LoadData_Progression();
	Data.Progression = EGameProgression::Loop;
	USaveManager::SaveData_Progression(Data);

	FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();
	switch (Info.InteractType)
	{
	case EInteractType::DoorOpen:
		MoveToHandlePlayer();
		PlayHandleTwistSound();
		break;
	}
}

#pragma endregion

#pragma region FirstDoorOpen

void AAnomaly_Object_Door::MoveToHandlePlayer()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AEHPlayerController* PC = Cast<AEHPlayerController>(Player->GetController());
	PC->SetPlayerInputAble(false);
	PC->SetIgnoreLookInput(true);

	FTransform WorldTarget = TargetPlayerTransform;
	FRotator TargetRotation = WorldTarget.Rotator();
	FVector TargetLocation = WorldTarget.GetLocation();

	TargetLocation.X -= 30.0f;
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
	TargetLocation.X -= 30.0f;
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
	OpenDoor();

	FTimerHandle DoorPushHandle;
	GetWorld()->GetTimerManager().SetTimer(DoorPushHandle, FTimerDelegate::CreateWeakLambda(this, [this, EHPC, Player]()
		{
			FVector TargetLocation = PushPlayerTransform.GetLocation() + FVector(-30.0f, 0.0f, 0.0f);

			Player->SetActorLocation(TargetLocation, false, nullptr, ETeleportType::TeleportPhysics);

			EHPC->OnPushDoorCompleted();
			EHPC->SetIgnoreLookInput(false);
		}), 1.0f, false);
}

#pragma endregion

#pragma region Normal

void AAnomaly_Object_Door::ReadyDoor()
{
	bIsDoorOpened = false;
	Component_Interact->RestoreInteract();
	Object->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	Object->SetCollisionResponseToChannel(ECC_Camera, ECR_Block);
	GetRootComponent()->SetWorldTransform(OriginalTransform);

	Timeline_Open->Stop();
}

void AAnomaly_Object_Door::ReadyDoorOpened()
{
	GetRootComponent()->SetWorldTransform(DoorOpenTransform);
}

void AAnomaly_Object_Door::SetLight(bool bIsStartFloor)
{
	Object->SetLightingChannels(true, false, bIsStartFloor);
}

#pragma endregion