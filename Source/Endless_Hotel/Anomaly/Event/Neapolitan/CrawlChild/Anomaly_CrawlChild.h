// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Anomaly/Event/Neapolitan/Anomaly_Event_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_CrawlChild.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_CrawlChild : public AAnomaly_Event_Neapolitan
{
	GENERATED_BODY()

#pragma region Base

#pragma endregion

#pragma region Activity

protected:
	virtual void SetAnomalyState() override;
	virtual void DisableAnomaly() override;

#pragma endregion

#pragma region CrawlChild

protected:
	UPROPERTY()
	TWeakObjectPtr<class UCharacterMovementComponent> PlayerMC;

	float OriginalSpeed;

#pragma endregion

};
