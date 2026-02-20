// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Event.h"
#include <CoreMinimal.h>
#include <Anomaly_Event_EightExit.generated.h>

#pragma region Declare

class UGameSystem;

#pragma endregion


// Anomaly_Event_EightExit.h
UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Event_EightExit : public AAnomaly_Event
{
    GENERATED_BODY()
#pragma region Base

public:
    AAnomaly_Event_EightExit(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

#pragma endregion

};

