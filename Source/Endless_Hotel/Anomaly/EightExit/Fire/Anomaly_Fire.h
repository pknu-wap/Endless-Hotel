// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Fire.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Fire : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()
	
#pragma region Activity

public:
	virtual void ActivateAnomaly() override;

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

	FTimerHandle FireHandle;

	UPROPERTY(EditAnywhere, Category = "Fire")
	float FireSpawnDuration;

	uint8 CurrentSpawnIndex = 0;

#pragma endregion

};