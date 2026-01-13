// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include "Anomaly_Shrink.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Shrink : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Shrink(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	TObjectPtr<class USkeletalMeshComponent> PlayerSM;

	UPROPERTY()
	TObjectPtr<class UCharacterMovementComponent> PlayerMC;

#pragma endregion

#pragma region Activity

public:
	virtual void ActivateAnomaly() override;

#pragma endregion

#pragma region Shrink

protected:
	UFUNCTION()
	void ShrinkPlayer(float Value);

protected:
	UPROPERTY()
	TObjectPtr<class UTimelineComponent> Timeline_Shrink;

	UPROPERTY(EditAnywhere, Category = "Anomaly|Time")
	TObjectPtr<UCurveFloat> Curve_Shrink;

	FVector OriginalScale;
	float OriginalSpeed;

#pragma endregion

};