// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Base/Anomaly_Event_Neapolitan.h"
#include "Anomaly_Cart.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Cart : public AAnomaly_Event_Neapolitan
{
	GENERATED_BODY()

#pragma region Activity

public:
	virtual void SetAnomalyState() override;

#pragma endregion

};
