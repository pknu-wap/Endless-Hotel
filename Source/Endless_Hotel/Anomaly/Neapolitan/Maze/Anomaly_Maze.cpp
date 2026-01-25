// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Neapolitan/Maze/Anomaly_Maze.h"

#pragma region Base

AAnomaly_Maze::AAnomaly_Maze(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

#pragma endregion

#pragma region Position

FVector AAnomaly_Maze::GetAnomalyStartPos() const
{
	return MazeStartPos;
}

#pragma endregion