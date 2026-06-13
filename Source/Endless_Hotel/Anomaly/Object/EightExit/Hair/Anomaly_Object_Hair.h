// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Object/EightExit/Anomaly_Object_EightExit.h"
#include "Anomaly_Object_Hair.generated.h"

class AActor;
class UCameraComponent;
class UCurveFloat;
class UMaterialParameterCollection;
class UStaticMeshComponent;
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

	UPROPERTY()
	TObjectPtr<AActor> SpawnedHairActor;

	UPROPERTY(EditAnywhere, Category = "Hair|Spawn")
	TSubclassOf<AActor> HairActorClass;

	UPROPERTY(EditAnywhere, Category = "Hair|Spawn")
	FVector HairRelativeLocation = FVector(30.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, Category = "Hair|Spawn")
	FRotator HairRelativeRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, Category = "Hair")
	TObjectPtr<UMaterialParameterCollection> HairMPC;

	UPROPERTY(EditAnywhere, Category = "Hair")
	TObjectPtr<UCurveFloat> Curve_HairOpacity;

	UPROPERTY(EditAnywhere, Category = "Hair")
	TObjectPtr<UCurveFloat> Curve_HairLocation;

	UPROPERTY(EditAnywhere, Category = "Hair")
	FName Param_Opacity = TEXT("MP_HairOpacity");

	UPROPERTY(EditAnywhere, Category = "Hair")
	float ScheduleAnomaly = 0.5f;

	UPROPERTY()
	FVector InitialHairLocation;

	UFUNCTION()
	void SpawnHair();

	UFUNCTION()
	void UpdateHair(float Value);

	UFUNCTION()
	void ResetHair(bool bIsStart);

	bool bHairActive = false;

public:
	void StartHair();

	virtual void Reset() override;

#pragma endregion
};