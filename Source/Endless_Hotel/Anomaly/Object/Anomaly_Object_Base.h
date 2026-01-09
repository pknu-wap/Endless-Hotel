// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Actor/EHActor.h"
#include "Anomaly_Object_Base.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Base : public AEHActor
{
	GENERATED_BODY()

#pragma region Anomaly

public:
	uint8 AnomalyID;

#pragma endregion

#pragma region Player

protected:
	virtual void KillPlayer();

#pragma endregion
};