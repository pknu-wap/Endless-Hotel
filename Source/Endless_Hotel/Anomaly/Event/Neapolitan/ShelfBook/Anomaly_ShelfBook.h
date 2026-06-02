// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Anomaly/Event/Anomaly_Event_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_ShelfBook.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_ShelfBook : public AAnomaly_Event_Neapolitan
{
	GENERATED_BODY()

#pragma region Activity

public:
	virtual void SetAnomalyState() override;

#pragma endregion
};