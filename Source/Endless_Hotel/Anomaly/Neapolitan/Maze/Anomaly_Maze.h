// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include "Anomaly/Base/Anomaly_Base_Neapolitan.h"
#include "Anomaly_Maze.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Maze : public AAnomaly_Base_Neapolitan
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Maze(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Position

protected:
	virtual FVector GetAnomalyStartPos() const override;

protected:
	UPROPERTY(EditAnywhere, Category = "Position")
	FVector MazeStartPos = FVector(2000, -1500, 710);

#pragma endregion

};
