// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Object/Neapolitan/Cart/Anomaly_Object_Cart.h"
#include <Components/StaticMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Sound/SoundBase.h>

#pragma region Cart

void AAnomaly_Object_Cart::CartMoving()
{
	bIsPlaying = true;

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound_Move, GetActorLocation());

	StartLocation = GetActorLocation();
	StartYaw = GetActorRotation().Yaw;

	CurrentTime = 0.f;

	GetWorld()->GetTimerManager().SetTimer(MoveHandle, this, &AAnomaly_Object_Cart::MoveTick, 0.02f, true);
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
	}
}

void AAnomaly_Object_Cart::FinishMove()
{
	GetWorld()->GetTimerManager().ClearTimer(MoveHandle);
	bIsPlaying = false;
}

#pragma endregion