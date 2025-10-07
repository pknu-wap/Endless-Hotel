// Copyright by 2025-2 WAP Game 2 team

#include "Character/Character/EHCharacter.h"

#pragma region Base

AEHCharacter::AEHCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

#pragma endregion