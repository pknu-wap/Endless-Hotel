// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Bug.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Bug : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()

#pragma region Activity

public:
	virtual void SetAnomalyActivate() override;

protected:
	virtual void StartAnomalyAction() override;

#pragma endregion

#pragma region Bug

protected:
	void SpawnBugs();

protected:
	UPROPERTY(EditAnywhere, Category = "Bug")
	TArray<FVector> BugLocations;

	UPROPERTY(EditAnywhere, Category = "Bug")
	TSubclassOf<class AAnomaly_Object_Bug> BugClass;

#pragma endregion

};