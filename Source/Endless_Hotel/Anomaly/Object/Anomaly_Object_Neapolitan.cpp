// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Anomaly_Object_Neapolitan.h"

#pragma region Base

void AAnomaly_Object_Neapolitan::BeginPlay()
{
	Super::BeginPlay();

	bSolved = false;

	OriginalTransform = GetActorTransform();
}

#pragma endregion