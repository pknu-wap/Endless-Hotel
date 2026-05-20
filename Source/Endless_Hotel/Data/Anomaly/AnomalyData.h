// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/Anomaly/Type_AnomalyID.h"
#include <AnomalyData.generated.h>

USTRUCT(BlueprintType)
struct FAnomalyData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EAnomalyID AnomalyID = EAnomalyID::None;
};