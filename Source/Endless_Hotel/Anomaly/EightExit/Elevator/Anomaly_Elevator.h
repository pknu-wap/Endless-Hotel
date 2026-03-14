// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Elevator.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Elevator : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Elevator

private:
	TWeakObjectPtr<class AElevator> TargetElevator;

#pragma endregion

#pragma region Anomaly



#pragma endregion

#pragma region Activity

public:
	virtual void SetAnomalyState() override;

#pragma endregion

};
