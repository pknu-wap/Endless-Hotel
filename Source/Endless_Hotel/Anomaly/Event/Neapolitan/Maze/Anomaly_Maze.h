// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Event/Anomaly_Event_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Maze.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Maze : public AAnomaly_Event_Neapolitan
{
	GENERATED_BODY()

#pragma region Anomaly

public:
	virtual void SetAnomalyState() override;

#pragma endregion

};