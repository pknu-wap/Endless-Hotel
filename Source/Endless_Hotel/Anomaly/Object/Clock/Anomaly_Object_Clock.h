// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Anomaly_Object_Neapolitan.h"
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

#pragma endregion

#pragma region Interact

public:
	virtual void Interacted_Implementation() override;

#pragma endregion

#pragma region Clock

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> SM_Bar;

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

#pragma endregion

#pragma region Ringing

public:
	UFUNCTION()
	void RingingClock();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> AC_Ringing;

	FTimerHandle TurnOffHandle;
	bool bInTime = false;

#pragma endregion

};