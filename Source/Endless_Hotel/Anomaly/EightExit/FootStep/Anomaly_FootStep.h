// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include "Anomaly_FootStep.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_FootStep : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()

#pragma region Activity

public:
	virtual void ActivateAnomaly() override;

#pragma endregion

#pragma region FootStep

protected:
	void FootStep();
#pragma endregion
};
