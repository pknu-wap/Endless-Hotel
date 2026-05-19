// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/Anomaly/Type_AnomalyID.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include <CoreMinimal.h>
#include <Type_AnomalyType.generated.h>

USTRUCT(BlueprintType)
struct FAnomalyEntry
{
	GENERATED_BODY()

	UPROPERTY()
	EAnomalyID AnomalyID = EAnomalyID::None;

	UPROPERTY()
	TSoftClassPtr<class AAnomaly_Event> AnomalyClass;

	UPROPERTY()
	TArray<TSoftClassPtr<AAnomaly_Object_Base>> ObjectClasses;
};