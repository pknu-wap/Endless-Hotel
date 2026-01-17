// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Door.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Door : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()

#pragma region Activity

public:
	virtual void ActivateAnomaly() override;

#pragma endregion

#pragma region Shake

protected:
	void DoorShake();

protected:
	uint8 CurrentIndex = 1;
	const uint8 MaxIndex = 10;

	float NextActionDelay = 1.f;

#pragma endregion

};