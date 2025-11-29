// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include "Anomaly_Light.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Light : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()
	
#pragma region Activity

public:
	virtual void ActivateAnomaly(uint8 Anomaly_ID) override;

#pragma endregion

#pragma region Light

protected:
	virtual void StartAnomalyAction() override;

protected:
	uint8 CurrentIndex = 1;
	const uint8 MaxIndex = 15;

	float NextActionDelay = 0;

#pragma endregion

};