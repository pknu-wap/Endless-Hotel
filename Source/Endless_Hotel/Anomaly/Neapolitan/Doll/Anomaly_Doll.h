// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Event_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Doll.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Doll : public AAnomaly_Event_Neapolitan
{
	GENERATED_BODY()


#pragma region Activity
public:
	virtual void SetAnomalyState() override;
#pragma endregion

};