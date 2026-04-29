// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Anomaly/Base/Anomaly_Event_Neapolitan.h>
#include <Anomaly_BackChild.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_BackChild : public AAnomaly_Event_Neapolitan
{
	GENERATED_BODY()

#pragma region Base

#pragma endregion

#pragma region Activity

protected:
	virtual void SetAnomalyState() override;
	virtual void DisableAnomaly() override;

#pragma endregion

#pragma region BackChild

protected:
	UPROPERTY()
	TWeakObjectPtr<class UCharacterMovementComponent> PlayerMC;

	float OriginalSpeed;

#pragma endregion

};
