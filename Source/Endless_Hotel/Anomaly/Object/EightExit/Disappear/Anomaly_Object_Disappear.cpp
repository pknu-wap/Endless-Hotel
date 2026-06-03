// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/EightExit/Disappear/Anomaly_Object_Disappear.h"

#pragma region Activity

void AAnomaly_Object_Disappear::StartDisappear()
{
	SetActorHiddenInGame(true);
}

#pragma endregion

#pragma region Reset

void AAnomaly_Object_Disappear::Reset()
{
	Super::Reset();

	SetActorHiddenInGame(false);
}

#pragma endregion