// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Door/Anomaly_Object_Door.h"
#include <Components/StaticMeshComponent.h>
#include <Components/TimelineComponent.h>
#include <Components/AudioComponent.h>
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>

#pragma region Base

AAnomaly_Object_Door::AAnomaly_Object_Door(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Mesh_Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Door"));
	SetRootComponent(Mesh_Door);
	Mesh_Door->SetRelativeRotation(FRotator(0, 0, 90));

	Mesh_Handle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Handle"));
	Mesh_Handle->SetupAttachment(RootComponent);

	Timeline_Door = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_Door"));
	Timeline_Handle = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_Handle"));

	AC_Effect = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_Effect"));
	AC_Effect->SetupAttachment(RootComponent);

	AC_Voice = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_Voice"));
	AC_Voice->SetupAttachment(RootComponent);
	
	AC_DoorMove = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_DoorMove"));
	AC_DoorMove->SetupAttachment(RootComponent);
	AC_DoorMove->bAutoActivate = false;

	TriggerBox_Open = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox_Open"));
	TriggerBox_Open->SetupAttachment(RootComponent);

	TriggerBox_Close = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox_Close"));
	TriggerBox_Close->SetupAttachment(RootComponent);

}

void AAnomaly_Object_Door::BeginPlay()
{
	Super::BeginPlay();

	Door_Origin = GetActorLocation();
	Handle_Origin = Mesh_Handle->GetRelativeLocation();

	FOnTimelineFloat Update_Door;
	Update_Door.BindUFunction(this, FName("ShakeDoor"));
	Timeline_Door->AddInterpFloat(Curve_Door, Update_Door);

	FOnTimelineFloat Update_Handle;
	Update_Handle.BindUFunction(this, FName("ShakeHandle"));
	Timeline_Handle->AddInterpFloat(Curve_Handle, Update_Handle);

	TriggerBox_Open->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TriggerBox_Open->SetGenerateOverlapEvents(false);

	TriggerBox_Close->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TriggerBox_Close->SetGenerateOverlapEvents(false);

	if (DoorIndex == 8)
	{
		OriginYaw = Mesh_Door->GetRelativeRotation().Yaw;
		CurrentYaw = OriginYaw;

		TriggerBox_Open->SetCollisionResponseToAllChannels(ECR_Ignore);
		TriggerBox_Open->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

		TriggerBox_Close->SetCollisionResponseToAllChannels(ECR_Ignore);
		TriggerBox_Close->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

		TriggerBox_Open->OnComponentBeginOverlap.AddDynamic(this, &AAnomaly_Object_Door::OnTriggerBox_OpenBeginOverlap);
		TriggerBox_Close->OnComponentBeginOverlap.AddDynamic(this, &AAnomaly_Object_Door::OnTriggerBox_CloseBeginOverlap);
	}
}

#pragma endregion

#pragma region Shake

void AAnomaly_Object_Door::ShakeDoor(float Value)
{
	FVector Target = Door_Origin;
	Target.Y += Value;

	Mesh_Door->SetWorldLocation(Target);
}

void AAnomaly_Object_Door::ShakeHandle(float Value)
{
	FVector Target = Handle_Origin;
	Target.Y += Value;

	Mesh_Handle->SetRelativeLocation(Target);
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

	GetWorld()->GetTimerManager().SetTimer(HandleHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			Timeline_Handle->PlayFromStart();
			ShakeCount_Handle++;

			if (ShakeCount_Handle >= MaxShakeCount_Handle)
			{
				GetWorld()->GetTimerManager().ClearTimer(HandleHandle);

				ShakeCount_Handle = 0;

				PlayShake_Door();
			}
		}), 0.17f, true);
}

void AAnomaly_Object_Door::PlayShake_Door()
{
	Timeline_Door->PlayFromStart();

	GetWorld()->GetTimerManager().SetTimer(DoorHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			Timeline_Door->PlayFromStart();
			ShakeCount_Door++;

			if (ShakeCount_Door >= MaxShakeCount_Door)
			{
				GetWorld()->GetTimerManager().ClearTimer(DoorHandle);

				ShakeCount_Door = 0;
			}
		}), 0.3f, true);
}

#pragma endregion

#pragma region Activity
void AAnomaly_Object_Door::ActivateDoorAnomaly()
{
	bOpenTriggered = false;
	bCloseTriggered = false;

	if (TriggerBox_Open)
	{
		TriggerBox_Open->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		TriggerBox_Open->SetGenerateOverlapEvents(true);
	}

	if (TriggerBox_Close)
	{
		TriggerBox_Close->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		TriggerBox_Close->SetGenerateOverlapEvents(false);
	}
}

#pragma region Open
void AAnomaly_Object_Door::OnTriggerBox_OpenBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OverlappedComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{ 
	if (bOpenTriggered) 
	{
		return;
	}

	if (OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		bOpenTriggered = true;
		StartRotateOpen();
		PlayOpen_Door();
	}
}

void AAnomaly_Object_Door::StartRotateOpen()
{
	GetWorld()->GetTimerManager().ClearTimer(RotateHandle);

	CurrentYaw = Mesh_Door->GetRelativeRotation().Yaw;
	TargetYaw = OriginYaw + OpenYawDelta;

	GetWorld()->GetTimerManager().SetTimer(RotateHandle, this, &AAnomaly_Object_Door::UpdateRotate, 0.01f, true);
}


void AAnomaly_Object_Door::PlayOpen_Door()
{
	if(!AC_DoorMove->IsPlaying())
	{
		AC_DoorMove->SetSound(Sound_DoorOpen);
		AC_DoorMove->Play();

		TriggerBox_Close->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		TriggerBox_Close->SetGenerateOverlapEvents(true);

		TriggerBox_Open->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		TriggerBox_Open->SetGenerateOverlapEvents(false);
	}
}
#pragma endregion

#pragma region Close
void AAnomaly_Object_Door::OnTriggerBox_CloseBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OverlappedComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bCloseTriggered)
	{
		return;
	}
	if (OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		bCloseTriggered = true;
		StartRotateClose();
		PlayClose_Door();
	}
}

void AAnomaly_Object_Door::StartRotateClose()
{
	GetWorld()->GetTimerManager().ClearTimer(RotateHandle);

	CurrentYaw = Mesh_Door->GetRelativeRotation().Yaw;
	TargetYaw = OriginYaw;

	GetWorld()->GetTimerManager().SetTimer(RotateHandle, this, &AAnomaly_Object_Door::UpdateRotate, 0.01f, true);
}

void AAnomaly_Object_Door::PlayClose_Door()
{
	if (!AC_DoorMove->IsPlaying())
	{
		AC_DoorMove->SetSound(Sound_DoorClose);
		AC_DoorMove->Play();

		TriggerBox_Close->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		TriggerBox_Close->SetGenerateOverlapEvents(false);
	}
}
#pragma endregion

#pragma region Rotate
void AAnomaly_Object_Door::UpdateRotate()
{
	const float NewYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, GetWorld()->GetDeltaSeconds(), RotateSpeed);
	CurrentYaw = NewYaw;

	FRotator Rot = Mesh_Door->GetRelativeRotation();
	Rot.Yaw = CurrentYaw;
	Mesh_Door->SetRelativeRotation(Rot);

	if (FMath::IsNearlyEqual(CurrentYaw, TargetYaw, 0.1f))
	{
		GetWorld()->GetTimerManager().ClearTimer(RotateHandle);
	}
}
#pragma endregion