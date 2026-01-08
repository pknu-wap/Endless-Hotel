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

#pragma region Interact
public:
	virtual void ActivateInteraction() override;

protected:
	virtual void Interacted_Implementation() override;

	void InteractRotate();

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