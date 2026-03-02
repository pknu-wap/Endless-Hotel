// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Event_EightExit.h"
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

protected:
	virtual void DisableAnomaly() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Activity")
	float FireDuration;

#pragma endregion

#pragma region Fire

protected:
	void SpawnFires();

protected:
	UPROPERTY(EditAnywhere, Category = "Fire")
	TSubclassOf<class AAnomaly_Object_Fire> FireClass;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TArray<FVector> FireSpawnPositions;

	UPROPERTY(EditAnywhere, Category = "Fire")
	TArray<TObjectPtr<class UNiagaraSystem>> NS_Fires;

	UPROPERTY()
	TArray<TObjectPtr<class AAnomaly_Object_Fire>> SpawnedFires;

	FTimerHandle FireHandle;

	UPROPERTY(EditAnywhere, Category = "Fire")
	float FireSpawnDuration;

	uint8 CurrentSpawnIndex = 0;

#pragma endregion

#pragma region Smoke

protected:
	UFUNCTION()
	void SmokeTimer(bool bIsCrouch);

protected:
	FTimerHandle SmokeHandle;

#pragma endregion

};