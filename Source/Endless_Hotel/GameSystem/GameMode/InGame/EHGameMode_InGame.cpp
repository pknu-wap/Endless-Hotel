// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/GameMode/InGame/EHGameMode_InGame.h"
#include "GameSystem/Anomaly/Anomaly_Generator.h"

void AEHGameMode_InGame::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->SpawnActor<AAnomaly_Generator>(Generator);
}
