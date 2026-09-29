// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/EightExit/Anomaly_Object_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Hair.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Hair : public AAnomaly_Object_EightExit
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_Hair(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

#pragma endregion

#pragma region Reference

private:
	UPROPERTY()
	TWeakObjectPtr<class UCameraComponent> Camera;

	UPROPERTY()
	TWeakObjectPtr<class APlayerController> PC;

#pragma endregion

#pragma region Hair

private:
	void SlowDownHair();

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> SK_Hair;

	FTimerHandle MoveHandle;

	FVector OriginLoc = FVector::ZeroVector;
	FVector TargetLoc = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UAudioComponent> AC_Hair;

	bool bPlayAudio = false;

#pragma endregion

};