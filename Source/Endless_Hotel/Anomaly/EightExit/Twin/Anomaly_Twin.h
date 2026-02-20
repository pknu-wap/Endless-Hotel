// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Twin.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Twin : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Twin(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Activity

public:
	virtual void SetAnomalyActivate() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Anomaly|Twin")
	FVector SpawnLocation;

#pragma endregion

};
