// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Event/Anomaly_Event.h"
#include <CoreMinimal.h>
#include <Normal.generated.h>

#pragma region Declare

class UGameSystem;

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API ANormal : public AAnomaly_Event
{
	GENERATED_BODY()

#pragma region Activities

protected:
	virtual void SetAnomalyState() override;

#pragma endregion

};