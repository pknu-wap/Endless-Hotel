// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Base/Anomaly_Event_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Maze.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Maze : public AAnomaly_Event_Neapolitan
{
	GENERATED_BODY()
	

#pragma region Base

public:
	AAnomaly_Maze(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Anomaly

public:
	virtual void SetAnomalyActivate() override;

protected:
	virtual void StartAnomalyAction() override;

#pragma endregion

#pragma region MazeMonster

protected:
	void MazeMonster();

#pragma endregion

};
