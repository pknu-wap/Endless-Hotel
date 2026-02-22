// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Object/EightExit/Anomaly_Object_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_FootStep.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_FootStep : public AAnomaly_Object_EightExit
{
	GENERATED_BODY()

#pragma region FootStep

public:
	void ChangeFootStep();

#pragma endregion

};