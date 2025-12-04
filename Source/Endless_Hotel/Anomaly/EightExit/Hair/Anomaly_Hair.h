// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include "Curves/CurveFloat.h"
#include "Components/TimelineComponent.h"
#include "Anomaly_Hair.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Hair : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()

public:
	AAnomaly_Hair(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	virtual void ActivateAnomaly(uint8 Anomaly_ID) override;

protected:
	UPROPERTY()
	FTimeline HairTimeline;

	UPROPERTY()
	UStaticMeshComponent* HairMesh;

	UPROPERTY(EditAnywhere, Category = "Hair")
	UMaterialParameterCollection* HairMPC;

	UPROPERTY(EditAnywhere, Category = "Hair")
	UCurveFloat* Curve_HairOpacity;

	UPROPERTY(EditAnywhere, Category = "Hair")
	UCurveFloat* Curve_HairLocation;

	UPROPERTY(EditAnywhere, Category = "Hair")
	FName Param_Opacity = "Scalar";

	UFUNCTION()
	void UpdateHair(float Value);

	UFUNCTION()
	void HairFinished();

	UPROPERTY(EditAnywhere, Category = "Hair")
	float StartDelay = 0.5f;
};
