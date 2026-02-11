// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Anomaly_Object_Base.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Hair.generated.h>

class UTimelineComponent;

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Hair : public AAnomaly_Object_Base
{
	GENERATED_BODY()

public:
	AAnomaly_Object_Hair(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma region Hair

protected:
	UPROPERTY()
	TObjectPtr<UTimelineComponent> HairTimeline;

	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> HairMesh;

	UPROPERTY(EditAnywhere, Category = "Hair")
	TObjectPtr<UMaterialParameterCollection> HairMPC;

	UPROPERTY(EditAnywhere, Category = "Hair")
	TObjectPtr<UCurveFloat> Curve_HairOpacity;

	UPROPERTY(EditAnywhere, Category = "Hair")
	TObjectPtr<UCurveFloat> Curve_HairLocation;

	UPROPERTY(EditAnywhere, Category = "Hair")
	FName Param_Opacity = "Scalar";

	UFUNCTION()
	void UpdateHair(float Value);


	UPROPERTY(EditAnywhere, Category = "Hair")
	float ScheduleAnomaly = 0.5f;

public:
	void StartHair();
};
