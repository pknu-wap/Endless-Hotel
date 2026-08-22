// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Anomaly/Object/EightExit/Anomaly_Object_EightExit.h"
#include <CoreMinimal.h>
#include <AAnomaly_Object_WChair.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_WChair : public AAnomaly_Object_EightExit
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Object_WChair(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Wheel

protected:
	UPROPERTY(EditAnywhere, Category = "Wheel")
	TObjectPtr<UStaticMeshComponent> LeftWheel;

	UPROPERTY(EditAnywhere, Category = "Wheel")
	TObjectPtr<UStaticMeshComponent> RightWheel;

#pragma endregion

#pragma region Moving

public:
	void StartMove();

protected:
	UFUNCTION()
	void UpdateWheelSpin(float Value);

	UFUNCTION()
	void UpdateMove(float Value);

	UFUNCTION()
	void EndMove();

protected:
	UPROPERTY(EditAnywhere, Category = "Moving|Wheel")
	TObjectPtr<class UCurveFloat> CV_WheelSpin;

	UPROPERTY(EditAnywhere, Category = "Moving|Position")
	TObjectPtr<class UCurveFloat> CV_Move;

	UPROPERTY(EditAnywhere, Category = "Moving|Wheel")
	FRotator OriginalWheelRotation;

	UPROPERTY(EditAnywhere, Category = "Moving|Position")
	FVector StartLocation;

	UPROPERTY(EditAnywhere, Category = "Moving|Position")
	FVector EndLocation;

private:
	TObjectPtr<class UTimelineComponent> Timeline_WheelSpin;
	TObjectPtr<class UTimelineComponent> Timeline_Move;

#pragma endregion

#pragma region AI

public:
	void OnCrawlChildSpawnedHandler(class ACrawlChild* SpawnedCrawlChild);

#pragma endregion

};