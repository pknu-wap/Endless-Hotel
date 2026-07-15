// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include <CoreMinimal.h>
#include <SandClock.generated.h>

UCLASS()
class ENDLESS_HOTEL_API ASandClock : public AEHActor
{
	GENERATED_BODY()

#pragma region Base

public:
	ASandClock(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void Tick(float DeltaSeconds) override;

#pragma endregion

#pragma region Mesh

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> SM_SandClock;

#pragma endregion

#pragma region Rotate

public:
	void StartRotateClock();
	void StopRotateClock();

private:
	void RotateClock(float DeltaSeconds);

private:
	bool bStartRotate = false;

	FRotator OriginalRot;
	FQuat CurrentQuat;
	FQuat FinalQuat;

#pragma endregion

};