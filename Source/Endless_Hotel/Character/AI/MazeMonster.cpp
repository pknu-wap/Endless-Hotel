// Copyright by 2025-2 WAP Game 2 team

#include "Character/AI/MazeMonster.h"
#include "Character/AI/MazeMonsterController.h"
#include "Character/Character/EHCharacter.h"

AMazeMonster::AMazeMonster(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}
