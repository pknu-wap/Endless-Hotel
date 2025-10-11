// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Anomaly/Anomaly_Base/Anomaly_Base.h"
#include "Neapolitan_Anomaly_Base.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESS_HOTEL_API ANeapolitan_Anomaly_Base : public AAnomaly_Base
{
	GENERATED_BODY()
#pragma region Anomaly Active& DeActive

protected:

	virtual void ActivateAnomaly_Implementation() override;

#pragma endregion

#pragma region Anomaly Verdict

protected:

	UFUNCTION(BlueprintCallable, Category = "Anomaly|Verdict")
	void SetIsSolved(bool bIsSolved, bool bIsCorrectElevator);
#pragma endregion

};
