// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Event/EightExit/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Hair.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Hair : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()

#pragma region Activity

public:
	virtual void SetAnomalyState() override;
	virtual void DisableAnomaly() override;

#pragma endregion

#pragma region Spawn

private:
	void SpawnHair();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Hair")
	TSubclassOf<class AAnomaly_Object_Hair> HairClass;

	UPROPERTY()
	TObjectPtr<class AAnomaly_Object_Hair> Hair;

#pragma endregion

};