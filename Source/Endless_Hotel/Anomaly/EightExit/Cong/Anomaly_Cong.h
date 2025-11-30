// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include "Anomaly_Cong.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Cong : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()

#pragma region Activity

public:
	virtual void ActivateAnomaly(uint8 Anomaly_ID) override;

#pragma endregion

#pragma region Cong

protected:
	virtual void StartAnomalyAction() override;

protected:
	FTimerDelegate CongDelegate;
	FTimerHandle CongHandle;

	const uint8 MaxIndex = 50;
	uint8 CurrentIndex = 0;

	float NextCong = 3;

#pragma endregion

};