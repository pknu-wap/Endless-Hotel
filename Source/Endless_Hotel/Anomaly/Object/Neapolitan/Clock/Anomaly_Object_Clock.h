// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Clock.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Clock : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Object_Clock(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

#pragma endregion

#pragma region Reset

public:
	virtual void InitializeOnAnomalySpawned() override { StopRinging(); }

#pragma endregion

#pragma region Clock

public:
	void SetClockSpeed(float Value);

protected:
	void MoveClockHands();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> SM_Bar;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> SM_HourHand;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> SM_MinuteHand;

	FRotator OriginalHourHandRotation;
	FRotator OriginalMinuteHandRotation;

	double ClockElapsed = 0.0;

	int32 ClockSeconds = 0;

	float ClockSpeed = 1.f;

#pragma endregion

#pragma region Interact

protected:
	virtual void Interact(class AEHCharacter* Interacter) override;

#pragma endregion

#pragma region TikTok

protected:
	UFUNCTION()
	void StartTikTok();

	UFUNCTION()
	void UpdateTikTok(float Value);

protected:
	UPROPERTY()
	TObjectPtr<class UTimelineComponent> Timeline_TikTok;

	UPROPERTY(EditAnywhere, Category = "TikTok")
	TObjectPtr<class UCurveFloat> CV_TikTok;

	FRotator OriginalRotation;

protected:
	UFUNCTION()
	void PlayTikTokSound();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> AC_TikTok;

	UPROPERTY(EditAnywhere, Category = "TikTok")
	TObjectPtr<class USoundBase> Sound_Tick;

	UPROPERTY(EditAnywhere, Category = "TikTok")
	TObjectPtr<class USoundBase> Sound_Tock;

	bool bPlayTick = true;

#pragma endregion

#pragma region Ringing

public:
	UFUNCTION()
	void RingingClock();

protected:
	void StopRinging();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> AC_Ringing;

	FTimerHandle TurnOffHandle;
	bool bInTime = false;

#pragma endregion

};