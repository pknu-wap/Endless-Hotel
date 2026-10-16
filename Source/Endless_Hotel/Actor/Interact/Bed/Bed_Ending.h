// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Actor/Interact/InteractBase.h"
#include <CoreMinimal.h>
#include <Bed_Ending.generated.h>

UCLASS()
class ENDLESS_HOTEL_API ABed_Ending : public AInteractBase
{
	GENERATED_BODY()

#pragma region Interact

public:
	virtual void Interact(AEHCharacter* Interacter) override;

#pragma endregion

#pragma region Reference

private:
	UPROPERTY()
	TWeakObjectPtr<class AEHPlayerController> PC;

#pragma endregion

#pragma region Sleep

private:
	void MoveToBedForSleep();

	UFUNCTION()
	void SleepBadEnding();

	void StartControllerRotation(const FRotator& TargetRotation, float Duration);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Sleep")
	FTransform Trans_Sleep;

	FTimerHandle ControllerHandle;

	FRotator StartControllerRot;
	FRotator TargetControllerRot;

	float ControllerElapsed = 0.f;
	float ControllerDuration = 0.f;

#pragma endregion

};