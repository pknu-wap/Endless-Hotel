// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Cart.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Cart : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_Cart(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Cart

public:
	UFUNCTION()
	void CartMoving();

protected:
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> Sound_Move = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> SM_Cart_Wheel;

#pragma endregion

#pragma region Move

protected:
	FTimerHandle MoveHandle;

	float Duration = 6.f;
	float CurrentTime = 0.f;

	UPROPERTY(EditAnywhere, Category = "Cart")
	float RotateYawDelta = 90.f;

	UPROPERTY(EditAnywhere, Category = "Cart")
	float MoveDistance = 120.f;

	FVector StartLocation = FVector::ZeroVector;
	float StartYaw = 0.f;

	bool bIsPlaying = false;

protected:
	void MoveTick();
	void FinishMove();

#pragma endregion

#pragma region WheelTimeline

protected:
	UFUNCTION()
	void StartWheelSpin();

	UFUNCTION()
	void UpdateWheelSpin(float Value);

protected:
	UPROPERTY()
	TObjectPtr<class UTimelineComponent> Timeline_WheelSpin;

	UPROPERTY(EditAnywhere, Category = "Cart")
	TObjectPtr<class UCurveFloat> CV_WheelSpin;

	FRotator OriginalWheelRotation;

#pragma endregion

};