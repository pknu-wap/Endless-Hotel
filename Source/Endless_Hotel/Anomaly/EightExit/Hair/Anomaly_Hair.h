// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Hair.generated.h>

class UCurveFloat;
class UMaterialParameterCollection;
class UTimelineComponent;
class UStaticMeshComponent;

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Hair : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()

public:
	AAnomaly_Hair(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Activity

public:
	virtual void SetAnomalyActivate() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Anomaly|Hair")
	FVector SpawnLocation;

#pragma endregion

};