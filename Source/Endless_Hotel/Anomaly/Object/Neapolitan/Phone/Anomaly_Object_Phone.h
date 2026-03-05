// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Anomaly_Object_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Phone.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Phone : public AAnomaly_Object_Neapolitan
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Object_Phone(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Interact

protected:
	virtual void SetInteraction() override;

	void RingingInteraction();

#pragma endregion

#pragma region Ringing

public:
	UFUNCTION()
	void RingingPhone();

protected:
	void MovePhone();
	void ShakePhone();

	UFUNCTION()
	void UpdateShake(float Value);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> AC;

	UPROPERTY(EditAnywhere, Category = "Ringing")
	TObjectPtr<class USoundWave> SW_Voice;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTimelineComponent> Timeline_Ringing;

	UPROPERTY(EditAnywhere, Category = "Ringing")
	TObjectPtr<class UCurveFloat> CV_Ringing;

	FTimerHandle MoveHandle;
	FTimerHandle ShakeHandle;

	bool bUp = true;

	FVector OriginalLocation;
	FVector UpLocation;

	UPROPERTY(EditAnywhere)
	float MoveValue = 10;

#pragma endregion

};