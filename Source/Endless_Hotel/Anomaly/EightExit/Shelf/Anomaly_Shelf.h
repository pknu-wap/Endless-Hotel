// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Shelf.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Shelf : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()
	
#pragma region Activity

public:
	virtual void SetAnomalyState() override;

#pragma endregion
};
