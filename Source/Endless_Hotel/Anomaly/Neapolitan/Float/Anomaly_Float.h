// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Event_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Float.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Float : public AAnomaly_Event_Neapolitan
{
	GENERATED_BODY()


#pragma region Activity

public:
	virtual void SetAnomalyActivate() override;

#pragma endregion

};
