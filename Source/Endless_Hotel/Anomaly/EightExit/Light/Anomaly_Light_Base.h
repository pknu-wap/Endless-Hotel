// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include "Anomaly_Light_Base.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Light_Base : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Activity

public:
	virtual void ActivateAnomaly_Implementation() override;

#pragma endregion

#pragma region Light

protected:
	void StartLightAction(TFunction<void(class AAnomaly_Object_Light*)> Action);

	TFunction<void(class AAnomaly_Object_Light*)> LightAction;

protected:
	int32 CurrentIndex = 1;
	const int32 MaxIndex = 4;

#pragma endregion

};