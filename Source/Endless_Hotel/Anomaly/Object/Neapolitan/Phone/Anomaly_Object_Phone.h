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
	virtual void Interact_Implementation() override;

#pragma endregion

#pragma region Ringing

public:
	UFUNCTION()
	void RingingPhone();

protected:
	void MovePhone();
	void ShakePhone();

	UFUNCTION()
	void UpdateMove(float Value);

	UFUNCTION()
	void UpdateShake(float Value);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> SM_Receiver;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> AC;

	UPROPERTY(EditAnywhere, Category = "Ringing")
	TObjectPtr<class USoundWave> SW_Voice;

	UPROPERTY()
	TObjectPtr<class UTimelineComponent> Timeline_Move;

	UPROPERTY()
	TObjectPtr<class UTimelineComponent> Timeline_Ringing;

	UPROPERTY(EditAnywhere, Category = "Ringing")
	TObjectPtr<class UCurveFloat> CV_Move;

	UPROPERTY(EditAnywhere, Category = "Ringing")
	TObjectPtr<class UCurveFloat> CV_Ringing;

	FTimerHandle MoveHandle;
	FTimerHandle ShakeHandle;

	FTransform OriginalTrans;

#pragma endregion

};