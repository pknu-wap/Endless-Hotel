// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Anomaly/Event/Neapolitan/Anomaly_Event_Neapolitan.h"
#include <CoreMinimal.h>
#include <Anomaly_Maze.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Maze : public AAnomaly_Event_Neapolitan
{
	GENERATED_BODY()

#pragma region Anomaly

public:
	virtual void SetAnomalyState() override;
	virtual void InteractSolveVerdict() override;
	virtual void DisableAnomaly() override;

protected:
	UPROPERTY(EditAnywhere, Category = "AI|Wall")
	TWeakObjectPtr<class AAnomaly_Object_Maze> TargetWall;

#pragma endregion

};