// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/EightExit/Anomaly_Object_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Hair.generated.h>

class UTimelineComponent;

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Hair : public AAnomaly_Object_EightExit
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_Hair(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

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

	UFUNCTION()
	void ResetHair(bool bIsStart);

	UPROPERTY(EditAnywhere, Category = "Hair")
	float ScheduleAnomaly = 0.5f;

	FVector InitialHairLocation;

public:
	void StartHair();
};
