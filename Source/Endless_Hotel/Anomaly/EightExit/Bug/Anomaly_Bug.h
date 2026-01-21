// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Bug.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Bug : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()

#pragma region Activity

public:
	virtual void ActivateAnomaly() override;

#pragma endregion

#pragma region Bug

protected:
	void SpawnBugs();

protected:
	UPROPERTY(EditAnywhere, Category = "Bug")
	TObjectPtr<class UNiagaraSystem> NS_Bug;

	UPROPERTY(EditAnywhere, Category = "Bug")
	TArray<FVector> BugLocations;

#pragma endregion

};