// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Neapolitan/Maze/Anomaly_Maze.h"

#pragma region Base

AAnomaly_Maze::AAnomaly_Maze(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PlayerStartTransform.SetLocation(FVector(2000, -1500, 710));
}

#pragma endregion