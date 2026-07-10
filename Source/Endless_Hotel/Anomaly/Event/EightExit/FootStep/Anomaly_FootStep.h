// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Event/EightExit/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_FootStep.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_FootStep : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()

#pragma region Activity

public:
	virtual void SetAnomalyState() override;
	virtual void DisableAnomaly() override;

protected:
	virtual void StartAnomalyAction() override;

#pragma endregion

#pragma region FootStep

private:
	void ChangeFootStep(bool bIsStart);

#pragma endregion

};