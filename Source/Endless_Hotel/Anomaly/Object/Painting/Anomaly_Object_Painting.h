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

	UPROPERTY(EditAnyWhere, Category = "Painting")
	TObjectPtr<class UStaticMeshComponent> Mesh_Painting;

	UPROPERTY(EditAnyWhere, Category = "Eye")
	TObjectPtr<class UStaticMeshComponent> Mesh_LeftEye;

	UPROPERTY(EditAnyWhere, Category = "Eye")
	TObjectPtr<class UStaticMeshComponent> Mesh_RightEye;

#pragma endregion

#pragma region EyeMove

public:
	void EyeFollowing();

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

#pragma endregion

#pragma region FrameTilt

public:
	void FrameTilt();

protected:
	UPROPERTY()
	TMap<TWeakObjectPtr<AActor>, FRotator> FrameInitialRotMap;

	UPROPERTY()
	FTimerHandle FrameTiltDelayHandle;

	UPROPERTY()
	FTimerHandle FrameTiltInterpHandle;

	UPROPERTY()
	float FrameTiltStartTime = 0.f;

	UPROPERTY()
	float FrameTiltDuration = 0.5f;

	UPROPERTY()
	float FrameTiltTargetRoll = 0.f;

	UPROPERTY(EditAnywhere, Category = "FrameTilt")
	float FrameTiltDelay = 10.f;

	UPROPERTY(EditAnywhere, Category = "FrameTilt")
	float FrameTiltInterpMin = 0.2f;

	UPROPERTY(EditAnywhere, Category = "FrameTilt")
	float FrameTiltInterpMax = 1.0f;

	UPROPERTY(EditAnywhere, Category = "FrameTilt")
	float FrameTiltRollMin = -180.f;

	UPROPERTY(EditAnywhere, Category = "FrameTilt")
	float FrameTiltRollMax = 180.f;

#pragma endregion

#pragma region Interact
	virtual void Interacted_Implementation() override;
	virtual void ShowInteractWidget_Implementation(bool bIsShow) override;

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