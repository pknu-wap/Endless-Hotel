// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Hair.generated.h>

class UCurveFloat;
class UMaterialParameterCollection;
class UTimelineComponent;
class UStaticMeshComponent;

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Hair : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()

public:
	AAnomaly_Hair(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:
	virtual void ActivateAnomaly() override;


#pragma region Trigger

public:
	virtual void ActiveTrigger() override;

	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

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


	UPROPERTY(EditAnywhere, Category = "Hair")
	float StartDelay = 0.5f;
};

#pragma endregion
