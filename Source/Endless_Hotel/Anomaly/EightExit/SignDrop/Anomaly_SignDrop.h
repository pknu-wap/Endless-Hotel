// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_SignDrop.generated.h>


UCLASS()
class ENDLESS_HOTEL_API AAnomaly_SignDrop : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_SignDrop(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Activity

public:
	virtual void SetAnomalyActivate() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Anomaly|Sign")
	FVector SpawnLocation;

#pragma endregion

};
