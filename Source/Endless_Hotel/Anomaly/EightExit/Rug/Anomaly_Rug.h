// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Rug.generated.h>

UCLASS()

class ENDLESS_HOTEL_API AAnomaly_Rug : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Rug();

#pragma endregion

#pragma region Activity

protected:
	virtual void SetAnomalyActivate() override;

#pragma endregion

};
