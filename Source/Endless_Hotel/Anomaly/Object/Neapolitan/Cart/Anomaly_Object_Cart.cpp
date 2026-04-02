// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/Neapolitan/Cart/Anomaly_Object_Cart.h"
#include <Components/StaticMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Sound/SoundBase.h>
#include <Components/TimelineComponent.h>

#pragma region Base

AAnomaly_Object_Cart::AAnomaly_Object_Cart(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SM_Cart_Wheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Cart_Wheel"));
	SM_Cart_Wheel->SetupAttachment(Object);

	Timeline_WheelSpin = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline_WheelSpin"));
}

void AAnomaly_Object_Cart::BeginPlay()
{
	Super::BeginPlay();

	OriginalWheelRotation = SM_Cart_Wheel->GetRelativeRotation();

	FOnTimelineFloat Update_WheelSpin;
	Update_WheelSpin.BindUFunction(this, "UpdateWheelSpin");
	Timeline_WheelSpin->AddInterpFloat(CV_WheelSpin, Update_WheelSpin);

	FOnTimelineEvent Finish_WheelSpin;
	Finish_WheelSpin.BindUFunction(this, "StartWheelSpin");
	Timeline_WheelSpin->SetTimelineFinishedFunc(Finish_WheelSpin);
}

#pragma endregion

#pragma region Cart

void AAnomaly_Object_Cart::CartMoving()
{
	bIsPlaying = true;

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound_Move, GetActorLocation());

	StartLocation = GetActorLocation();
	StartYaw = GetActorRotation().Yaw;

	CurrentTime = 0.f;

	GetWorld()->GetTimerManager().SetTimer(MoveHandle, this, &AAnomaly_Object_Cart::MoveTick, 0.02f, true);

	Timeline_WheelSpin->PlayFromStart();
}

#pragma endregion

#pragma region RotateMove

void AAnomaly_Object_Cart::MoveTick()
{
	CurrentTime += 0.02f;
	float Alpha = CurrentTime / Duration;

	float Yaw = StartYaw + RotateYawDelta * Alpha;
	SetActorRotation(FRotator(0, Yaw, 0));

	FVector Dir = GetActorForwardVector();
	FVector Target = StartLocation + Dir * MoveDistance;

	FVector NewLocation = FMath::Lerp(StartLocation, Target, Alpha);
	SetActorLocation(NewLocation);

	if (Alpha >= 1.f)
	{
		FinishMove();
		FinishMove();
	}
}

void AAnomaly_Object_Cart::FinishMove()
{
	GetWorld()->GetTimerManager().ClearTimer(MoveHandle);
	bIsPlaying = false;

	Timeline_WheelSpin->Stop();
}

#pragma endregion

#pragma region WheelTimeline

void AAnomaly_Object_Cart::StartWheelSpin()
{
	Timeline_WheelSpin->PlayFromStart();
}

void AAnomaly_Object_Cart::UpdateWheelSpin(float Value)
{
	FRotator Target = OriginalWheelRotation;
	Target.Pitch = Value;
	SM_Cart_Wheel->SetRelativeRotation(Target);
}
#pragma endregion