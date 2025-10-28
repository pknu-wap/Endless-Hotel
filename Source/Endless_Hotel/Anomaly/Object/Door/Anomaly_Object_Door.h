// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Anomaly_Object_Door.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Door : public AAnomaly_Object_Base
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Object_Door(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh_Door;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh_Handle;

	UPROPERTY()
	TObjectPtr<class UTimelineComponent> Timeline;

	UPROPERTY(EditAnywhere, Category = "Time")
	TObjectPtr<UCurveFloat> Curve_HandleShake;

#pragma endregion

#pragma region Handle Shake

public:
	UFUNCTION()
	void PlayHandleShake();

protected:
	UFUNCTION()
	void ShakeHandle(float Value);

#pragma endregion

};