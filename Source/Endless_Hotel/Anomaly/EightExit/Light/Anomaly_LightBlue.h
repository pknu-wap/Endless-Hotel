// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Anomaly_Base/Anomaly_Base_EightExit.h"
#include "Anomaly_LightBlue.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_LightBlue : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Activity

public:
	virtual void ActivateAnomaly_Implementation() override;

protected:
	int32 CurrentIndex = 1;
	const int32 MaxIndex = 4;

#pragma endregion

};