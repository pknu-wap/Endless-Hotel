// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Anomaly_Object_Painting.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Painting : public AAnomaly_Object_Base
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

#pragma region Trigger

public:
	void ActiveTrigger();

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> TriggerBox;

	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	uint8 CurrentAnomalyID = 0;

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

};