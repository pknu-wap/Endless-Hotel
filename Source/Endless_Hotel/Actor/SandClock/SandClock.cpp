// Copyright by 2026-1 WAP Game 2 team

#include "Actor/SandClock/SandClock.h"

#pragma region Base

ASandClock::ASandClock(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	SM_SandClock = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_SandClock"));
	SetRootComponent(SM_SandClock);
}

void ASandClock::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bStartRotate)
	{
		RotateClock(DeltaSeconds);
	}
}

#pragma endregion

#pragma region Rotate

void ASandClock::StartRotateClock()
{
	SetActorTickEnabled(true);

	bStartRotate = true;

	OriginalRot = GetActorRotation();
}

void ASandClock::StopRotateClock()
{
	SetActorTickEnabled(false);

	bStartRotate = false;

	SetActorRotation(OriginalRot);
}

void ASandClock::RotateClock(float DeltaSeconds)
{
	constexpr float RotateSpeed = 90.f;

	CurrentQuat = GetActorQuat();
	FinalQuat = CurrentQuat * FQuat(FVector::UpVector, FMath::DegreesToRadians(180));

	CurrentQuat = FMath::QInterpConstantTo(CurrentQuat, FinalQuat, DeltaSeconds, FMath::DegreesToRadians(RotateSpeed));
	SetActorRotation(CurrentQuat);
}

#pragma endregion