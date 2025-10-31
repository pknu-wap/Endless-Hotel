// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Base/Anomaly_Base_EightExit.h"
#include "Anomaly_Ceiling.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Ceiling : public AAnomaly_Base_EightExit
{
	GENERATED_BODY()

#pragma region Activity

public:
	virtual void ActivateAnomaly_Implementation(uint8 Anomaly_ID) override;

#pragma endregion

#pragma region Ceiling

protected:
	void StartCeilingAction();

protected:
	TFunction<void(class AAnomaly_Object_Ceiling*)> CeilingAction;

#pragma endregion
};
