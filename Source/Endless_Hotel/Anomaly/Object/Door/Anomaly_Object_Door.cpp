// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Door/Anomaly_Object_Door.h"
#include <Components/StaticMeshComponent.h>
#include <Components/TimelineComponent.h>
#include <Components/AudioComponent.h>
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>
#include <Components/CapsuleComponent.h>

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

	TriggerBox_Door5 = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox_Door5"));
	TriggerBox_Door5->SetupAttachment(RootComponent);
	TriggerBox_Door5->SetGenerateOverlapEvents(true);
	TriggerBox_Door5->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox_Door5->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TriggerBox_Door8 = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox_Door8"));
	TriggerBox_Door8->SetupAttachment(RootComponent);
	TriggerBox_Door8->SetGenerateOverlapEvents(true);
	TriggerBox_Door8->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox_Door8->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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

#pragma region DoorClose

AAnomaly_Object_Door* AAnomaly_Object_Door::FindDoorByIndex(int32 Index) const
{
	if (!GetWorld())
	{
		return nullptr;
	}

	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAnomaly_Object_Door::StaticClass(), AllActors);

	for (AActor* Actor : AllActors)
	{
		AAnomaly_Object_Door* Door = Cast<AAnomaly_Object_Door>(Actor);
		if (Door && Door->DoorIndex == Index)
		{
			return Door;
		}
	}
	return nullptr;
}

bool AAnomaly_Object_Door::IsPlayerCharacter(AActor* OtherActor) const
{
	return (OtherActor && UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AAnomaly_Object_Door::StartDoorClose()
{
	if (DoorIndex != 5)
	{
		return;
	}

	if (bDoor16Initialized)
	{
		return;
	}
	bDoor16Initialized = true;

	SetupDoor16Triggers();
}

void AAnomaly_Object_Door::SetupDoor16Triggers()
{
	AAnomaly_Object_Door* Door8 = FindDoorByIndex(8);
	if (!Door8)
	{
		return;
	}
	Door8Cached = Door8;
	Door8ObjectCached = Door8;

	const FVector BoxExtent = FVector(70.f, 130.f, 170.f);
	const float ForwardOffset = 300.f;

	TriggerBox_Door5->SetBoxExtent(BoxExtent);
	TriggerBox_Door8->SetBoxExtent(BoxExtent);

	const FVector Loc5 = GetActorLocation() + GetActorForwardVector() * ForwardOffset;
	const FVector Loc8 = Door8->GetActorLocation() + Door8->GetActorForwardVector() * ForwardOffset;

	TriggerBox_Door5->SetWorldLocation(Loc5);
	TriggerBox_Door8->SetWorldLocation(Loc8);

	TriggerBox_Door5->OnComponentBeginOverlap.RemoveAll(this);
	TriggerBox_Door8->OnComponentBeginOverlap.RemoveAll(this);

	TriggerBox_Door5->OnComponentBeginOverlap.AddDynamic(this, &AAnomaly_Object_Door::OnDoor16Trigger5Overlap);
	TriggerBox_Door8->OnComponentBeginOverlap.AddDynamic(this, &AAnomaly_Object_Door::OnDoor16Trigger8Overlap);

	SetTriggerEnabled(TriggerBox_Door5, true);
	SetTriggerEnabled(TriggerBox_Door8, false);
}

void AAnomaly_Object_Door::SetTriggerEnabled(UBoxComponent* TriggerBox, bool bEnabled)
{
	if (!TriggerBox)
	{
		return;
	}
	TriggerBox->SetCollisionEnabled(bEnabled ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
	TriggerBox->SetGenerateOverlapEvents(bEnabled);
	TriggerBox->SetHiddenInGame(!bEnabled);

	if (bEnabled)
	{
		TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
		TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
}

void AAnomaly_Object_Door::OnDoor16Trigger5Overlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsPlayerCharacter(OtherActor))
	{
		return;
	}
	AAnomaly_Object_Door* Door8 = Door8ObjectCached.Get();
	if (!Door8)
	{
		return;
	}
	SetTriggerEnabled(TriggerBox_Door5, false);
	SetTriggerEnabled(TriggerBox_Door8, true);
	Door8->SetDoorRotationZ(-135.f);

	if (AC_DoorMove && Sound_DoorOpen && !AC_DoorMove->IsPlaying())
	{
		AC_DoorMove->Sound = Sound_DoorOpen;
		AC_DoorMove->Play();
	}
}

void AAnomaly_Object_Door::OnDoor16Trigger8Overlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsPlayerCharacter(OtherActor))
	{
		return;
	}
	AAnomaly_Object_Door* Door8 = Door8ObjectCached.Get();
	if (!Door8)
	{
		return;
	}
	if (AC_DoorMove && Sound_DoorClose && !AC_DoorMove->IsPlaying())
	{
		AC_DoorMove->Sound = Sound_DoorClose;
		AC_DoorMove->Play();
	}
	SetTriggerEnabled(TriggerBox_Door8, false);
	
	const TArray<float> DeltaList = { -45.f, -10.f, 55.f };
	Door8->PlayDoorRotationDeltaSquence(DeltaList, 0.12f);
}

#pragma endregion

#pragma region DoorRotation

void AAnomaly_Object_Door::SetDoorRotationZ(float NewZ)
{
	if (!Mesh_Door)
	{
		return;
	}
	const FRotator Current = Mesh_Door->GetRelativeRotation();
	Mesh_Door->SetRelativeRotation(FRotator(Current.Pitch, Current.Yaw, NewZ));
}

void AAnomaly_Object_Door::PlayDoorRotationDeltaSquence(const TArray<float>& DeltaList, float StepInterval)
{
	if (!Mesh_Door)
	{
		return;
	}
	if (!GetWorld())
	{
		return;
	}
	if (DeltaList.Num() <= 0)
	{
		return;
	}
	GetWorld()->GetTimerManager().ClearTimer(RotationStepHandle);

	const FRotator Current = Mesh_Door->GetRelativeRotation();
	RotationBaseZ = Current.Roll;

	RotationDeltaList = DeltaList;
	RotationStepInterval = StepInterval;
	RotationStepIndex = 0;

	SetDoorRotationZ(RotationBaseZ + RotationDeltaList[RotationStepIndex]);

	GetWorld()->GetTimerManager().SetTimer(RotationStepHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			if (!GetWorld())
			{
				return;
			}
			RotationStepIndex++;
			if (RotationStepIndex >= RotationDeltaList.Num())
			{
				GetWorld()->GetTimerManager().ClearTimer(RotationStepHandle);
				RotationStepIndex = 0;
				return;
			}
			SetDoorRotationZ(RotationBaseZ + RotationDeltaList[RotationStepIndex]);
		}), RotationStepInterval, true);
}
#pragma endregion