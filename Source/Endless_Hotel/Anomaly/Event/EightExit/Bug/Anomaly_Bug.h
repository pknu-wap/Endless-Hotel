// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Event/EightExit/Anomaly_Event_EightExit.h"
#include <CoreMinimal.h>
#include <Anomaly_Bug.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Bug : public AAnomaly_Event_EightExit
{
	GENERATED_BODY()

#pragma region Activity

public:
	virtual void SetAnomalyState() override;
	virtual void DisableAnomaly() override;

#pragma endregion

#pragma region Bug

protected:
	void SpawnBugs();

	UPROPERTY(EditAnywhere, Category = "Bug")
	TObjectPtr<class UNiagaraSystem> NS_BugLong;

	UPROPERTY(EditAnywhere, Category = "Bug")
	TObjectPtr<class UNiagaraSystem> NS_BugShort;

private:
	UPROPERTY()
	TArray<TObjectPtr<class UNiagaraComponent>> SpawnedBugs;

#pragma endregion

};