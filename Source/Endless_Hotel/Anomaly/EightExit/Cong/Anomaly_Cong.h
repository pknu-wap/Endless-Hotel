// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Cong.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Cong : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()

#pragma region Activity

public:
	virtual void ActivateAnomaly() override;

#pragma endregion

#pragma region Cong

protected:
	void StartCongCong();

protected:
	FTimerDelegate CongDelegate;
	FTimerHandle CongHandle;

	const uint8 MaxIndex = 50;
	uint8 CurrentIndex = 0;

	float NextCong = 2.9f;

#pragma endregion

};