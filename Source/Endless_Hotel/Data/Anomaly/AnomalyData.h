// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "AnomalyData.generated.h"

USTRUCT(BlueprintType)
struct FAnomalyData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AnomalyID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Object_ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Anomaly_En;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AnomalyPath;
};