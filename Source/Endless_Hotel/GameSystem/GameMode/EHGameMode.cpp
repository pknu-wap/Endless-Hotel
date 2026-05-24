// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/GameMode/EHGameMode.h"

#pragma region Base

AEHGameMode::AEHGameMode(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

#pragma endregion