// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Type/Save/Type_Save.h"
#include "Actor/Interact/InteractBase.h"
#include <CoreMinimal.h>
#include <Bed.generated.h>

UCLASS()
class ENDLESS_HOTEL_API ABed : public AInteractBase
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Interact

public:
	virtual void Interact(AEHCharacter* Interacter) override;

#pragma endregion

#pragma region Reference

private:
	UPROPERTY()
	TWeakObjectPtr<class AEHPlayer> EHPlayer;

	UPROPERTY()
	TWeakObjectPtr<class AEHPlayerController> PC;

	UPROPERTY()
	TWeakObjectPtr<class AEHPlayerCameraManager> CameraManager;

#pragma endregion

#pragma region Progression

private:
	void OnChangedProgression(EGameProgression Target);

#pragma endregion

#pragma region Sleep

private:
	void MoveToBedStart();

	UFUNCTION()
	void MoveToBedMiddle();

	UFUNCTION()
	void MoveToBedEnd();

	void WakeUp();

	UFUNCTION()
	void OnCompletedWakeUp();

	void StartControllerRotation(const FRotator& TargetRotation, float Duration);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Sleep")
	FTransform Trans_Start;

	UPROPERTY(EditDefaultsOnly, Category = "Sleep")
	FTransform Trans_Middle;

	FTimerHandle ControllerHandle;

	FRotator StartControllerRot;
	FRotator TargetControllerRot;

	float ControllerElapsed = 0.f;
	float ControllerDuration = 0.f;

#pragma endregion

};