// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include "Anomaly_Light.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Light : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()
	
#pragma region Base
	
public:
	AAnomaly_Light(const FObjectInitializer& ObjectInitializer);

//protected:
//	virtual void BeginPlay() override;

#pragma endregion

#pragma region Activity

public:
	virtual void ActivateAnomaly() override;

#pragma endregion

#pragma region Light

protected:
	virtual void StartAnomalyAction() override;

protected:
	uint8 CurrentIndex = 1;
	const uint8 MaxIndex = 20;

	float NextActionDelay = 0.5f;

#pragma endregion

};