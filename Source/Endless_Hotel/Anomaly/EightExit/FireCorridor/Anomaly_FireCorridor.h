// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_FireCorridor.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_FireCorridor : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_FireCorridor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#pragma endregion
};