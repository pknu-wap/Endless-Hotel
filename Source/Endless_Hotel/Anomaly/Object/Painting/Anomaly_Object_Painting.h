// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Painting.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Painting : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_Painting(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditAnywhere, Category = "Painting")
	TObjectPtr<class USceneComponent> Root;

	UPROPERTY(EditAnyWhere, Category = "Eye")
	TObjectPtr<class UStaticMeshComponent> Mesh_LeftEye;

	UPROPERTY(EditAnyWhere, Category = "Eye")
	TObjectPtr<class UStaticMeshComponent> Mesh_RightEye;

	UPROPERTY(EditAnywhere, Category = "ObjectID")
	bool bIsPortrait = false;

#pragma endregion

#pragma region EyeMove

public:
	void EyeFollowing();

protected:
	UPROPERTY(EditAnywhere, Category = "EyeRotate")
	float EyeCorrection;

	UPROPERTY(EditAnywhere, Category = "EyeRotate")
	float YawLimitDeg;

	UPROPERTY(EditAnywhere, Category = "EyeRotate")
	float Sensitivity;

#pragma endregion

#pragma region Blood

public:
	void BloodDropping();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraComponent> Niagara_Blood_Left;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraComponent> Niagara_Blood_Right;

#pragma endregion


#pragma region Blur

public:
	void BlurPaint();

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TObjectPtr<class UWidgetComponent> Widget_PaintingBlur;

protected:
	UPROPERTY(EditAnywhere, Category = "PaintingBlur")
	TObjectPtr<class UMaterialInterface> BlurMaterial;

#pragma endregion

#pragma region FrameTilt

public:
	void FrameTilt();

protected:
	FTimerHandle FrameTiltHandle;
	float CurrentTilt = 0.f;
	float TargetTilt = 0.f;

#pragma endregion

#pragma region Interact

public:
	virtual void SetInteraction() override;

	void InteractRotate();

protected:
	UFUNCTION()
	void InteractedMoveStep(int32 step);

protected:
	UPROPERTY(EditAnywhere, Category = "Interact")
	FVector DefaultLocation;

	UPROPERTY(EditAnywhere, Category = "Interact")
	FVector InteractingLocation;

	UPROPERTY(EditAnywhere, Category = "Interact")
	FVector InteractedLocation;

	UPROPERTY(EditAnywhere, Category = "Interact")
	float RotateAngle = 180.f;

	FRotator OriginRotation;

	bool bIsRotated = false;

#pragma endregion

};