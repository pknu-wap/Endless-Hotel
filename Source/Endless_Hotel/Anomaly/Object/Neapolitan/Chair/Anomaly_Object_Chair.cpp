// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/Neapolitan/Chair/Anomaly_Object_Chair.h"
#include <Components/StaticMeshComponent.h>

#pragma region Base

AAnomaly_Object_Chair::AAnomaly_Object_Chair(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SM_Chair = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Chair"));
	SM_Chair->SetupAttachment(Object);
}

#pragma endregion

#pragma region Chair

void AAnomaly_Object_Chair::ChairMoving()
{
	bIsPlaying = true;

	StartLocation = GetActorLocation();
	StartYaw = GetActorRotation().Yaw;
	FRotator Rot = GetActorRotation();
	Rot.Yaw = StartYaw + RotateYawDelta;
	SetActorRotation(Rot);

	CurrentTime = 0.f;

	GetWorld()->GetTimerManager().SetTimer(MoveHandle, this, &AAnomaly_Object_Chair::MoveTick, 0.02f, true);
}

#pragma endregion

#pragma region RotateMove

void AAnomaly_Object_Chair::MoveTick()
{
	CurrentTime += 0.02f;
	float Alpha = CurrentTime / Duration;

	float Yaw = StartYaw + RotateYawDelta * Alpha;
	SetActorRotation(FRotator(0, Yaw, 0));

	FVector Dir = GetActorRightVector();
	FVector Target = StartLocation + Dir * MoveDistance;

	FVector NewLocation = FMath::Lerp(StartLocation, Target, Alpha);
	SetActorLocation(NewLocation);

	if (Alpha >= 1.f)
	{
		FinishMove();
	}
}

void AAnomaly_Object_Chair::FinishMove()
{
	GetWorld()->GetTimerManager().ClearTimer(MoveHandle);
	bIsPlaying = false;
}

#pragma endregion