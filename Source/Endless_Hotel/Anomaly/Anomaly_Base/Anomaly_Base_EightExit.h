// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Anomaly_Base/Anomaly_Base.h"
#include "Anomaly_Base_EightExit.generated.h"

// Anomaly_Base_EightExit.h
UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Base_EightExit : public AAnomaly_Base
{
    GENERATED_BODY()
#pragma region Base

public:
    AAnomaly_Base_EightExit(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#pragma endregion

#pragma region Activities

protected:
    virtual void ActivateAnomaly_Implementation() override;

#pragma endregion
};

