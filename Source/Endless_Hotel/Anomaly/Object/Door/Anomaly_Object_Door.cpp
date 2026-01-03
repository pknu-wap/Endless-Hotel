// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Door/Anomaly_Object_Door.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"

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