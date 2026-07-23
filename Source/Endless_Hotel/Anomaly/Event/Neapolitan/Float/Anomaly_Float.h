// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Event/Neapolitan/Anomaly_Event_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Float.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Float : public AAnomaly_Event_Neapolitan
{
	GENERATED_BODY()

#pragma region Activity

public:
	virtual void SetAnomalyState() override;

#pragma endregion

#pragma region Sound

private:
	void PlayGravitySound();

protected:
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> SW_Gravity;

#pragma endregion

};