// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Neapolitan/Maze/Anomaly_Maze.h"
#include "Anomaly/Object/Neapolitan/Maze/Anomaly_Object_Maze.h"
#include <Kismet/GameplayStatics.h>

#pragma region Base

AAnomaly_Maze::AAnomaly_Maze(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PlayerStartTransform.SetLocation(FVector(-3790, 640, -2852.849903f));
}

#pragma endregion

#pragma region Anomaly

void AAnomaly_Maze::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();

	switch (AnomalyName)
	{
	case EAnomalyName::Maze_Monster:
		AnomalyAction = ([](AAnomaly_Object_Base* Maze)
			{
				Cast<AAnomaly_Object_Maze>(Maze)->StartMazeMonster();
			});
		ScheduleAnomaly();
		break;
	}
}

#pragma endregion