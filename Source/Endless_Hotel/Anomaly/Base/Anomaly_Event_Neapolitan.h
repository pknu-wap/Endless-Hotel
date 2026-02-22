// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <Anomaly/Base/Anomaly_Event.h>
#include <CoreMinimal.h>
#include <Anomaly_Event_Neapolitan.generated.h>

// Anomaly_Event_Neapolitan.h
UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Event_Neapolitan : public AAnomaly_Event
{
    GENERATED_BODY()
#pragma region Base

public:
    AAnomaly_Event_Neapolitan(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
    virtual void BeginPlay() override;

#pragma endregion
};
