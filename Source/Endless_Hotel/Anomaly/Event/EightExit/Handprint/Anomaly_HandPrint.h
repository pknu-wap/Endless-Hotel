// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Event/EightExit/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_HandPrint.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_HandPrint : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()

#pragma region Activity

public:
	virtual void SetAnomalyState() override;

#pragma endregion

};