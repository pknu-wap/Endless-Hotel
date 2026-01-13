// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include "Anomaly/Base/Anomaly_Base.h"
#include "Normal.generated.h"

#pragma region Declare

class UAnomalyProgressSubSystem;

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API ANormal : public AAnomaly_Base
{
	GENERATED_BODY()
	
#pragma region Base

public:
	ANormal(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
#pragma endregion

#pragma region Activities

protected:
	virtual void ActivateAnomaly() override;

#pragma endregion
};
