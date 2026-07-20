// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Event/EightExit/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Fire.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Fire : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()
	
#pragma region Reference

protected:
	UPROPERTY()
	TWeakObjectPtr<class AEHPlayer> EHPlayer;

#pragma endregion

#pragma region Activity

public:
	virtual void SetAnomalyState() override;
	virtual void DisableAnomaly() override;

#pragma endregion

#pragma region Fire

private:
	void StartFire();
	void SpawnFires();

protected:
	UPROPERTY(EditAnywhere, Category = "Fire")
	TSubclassOf<class AAnomaly_Object_Fire> FireClass;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TArray<FVector> FireSpawnPositions;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TObjectPtr<class UNiagaraSystem> NS_Fire;

private:
	UPROPERTY()
	TArray<TObjectPtr<class AAnomaly_Object_Fire>> SpawnedFires;

	FTimerHandle FireHandle;

	uint8 FireSpawnIndex = 0;

#pragma endregion

#pragma region Smoke

private:
	UFUNCTION()
	void SmokeTimer(bool bIsCrouch);

	void SpawnSmokes();

protected:
	UPROPERTY(EditAnywhere, Category = "Smoke")
	TObjectPtr<class UNiagaraSystem> NS_Smoke;

	UPROPERTY(EditAnywhere, Category = "Smoke")
	TArray<FTransform> SmokeTransform;

private:
	FTimerHandle SmokeHandle;
	FTimerHandle JilsikHandle;

	uint8 SmokeSpawnIndex = 0;

	UPROPERTY()
	TArray<TObjectPtr<class UNiagaraComponent>> SpawnedSmokes;

#pragma endregion

#pragma region Sound

private:
	void PlayCoughSound();

protected:
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> SW_Cough;

private:
	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC;

#pragma endregion

};