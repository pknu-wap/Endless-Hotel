// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Event/EightExit/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_HandPrint.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_HandPrint : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()

#pragma region Activity

public:
	virtual void SetAnomalyState() override;
	virtual void DisableAnomaly() override;

#pragma endregion

#pragma region HandPrint

private:
	void SpawnHandPrint();

protected:
	UPROPERTY(EditAnywhere, Category = "HandPrint")
	TSubclassOf<class AAnomaly_Object_HandPrint> HandPrintClass;

	UPROPERTY(EditAnywhere, Category = "HandPrint")
	TArray<FTransform> HandPrintTrans;

private:
	UPROPERTY()
	TArray<TObjectPtr<class AAnomaly_Object_HandPrint>> SpawnedHandPrint;

#pragma endregion

#pragma region Light

private:
	void TurnAllLights(bool bOn);

#pragma endregion

};