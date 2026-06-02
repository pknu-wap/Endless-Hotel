// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Event/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Twin.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Twin : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()

#pragma region Activity

public:
	virtual void SetAnomalyState() override;
	virtual void DisableAnomaly() override;

#pragma endregion

};