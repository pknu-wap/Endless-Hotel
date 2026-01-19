// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_GhostHand.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_GhostHand : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()

#pragma region Acitvity
public:
	virtual void ActivateAnomaly() override;
#pragma endregion
};