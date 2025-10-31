// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Anomaly_Object_Ceiling.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Ceiling : public AAnomaly_Object_Base
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_Ceiling(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh_Default;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh_Ceiling;

	UPROPERTY()
	TObjectPtr<class UTimelineComponent> Timeline;

	UPROPERTY(EditAnywhere, Category = "Time")
	TObjectPtr<UCurveFloat> Curve_CeilingRotate;

#pragma endregion

#pragma region Ceiling Rotate

public:
	UFUNCTION()
	void PlayCeilingRotate();

protected:
	UFUNCTION()
	void CeilingRotate(float Value);

#pragma endregion
};
