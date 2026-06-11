// Copyright by 2025-2 WAP Game 2 team

#include "Character/AI/MazeMonster/MazeMonster.h"
#include "Components/AudioComponent.h"

AMazeMonster::AMazeMonster(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AttackAC = CreateDefaultSubobject<UAudioComponent>(TEXT("Attack_AC"));
	AttackAC->SetupAttachment(RootComponent);
	CurrentIndex = 0;
}

#pragma region Attack

void AMazeMonster::PlayAttackSound()
{
	AttackAC->Play();
}

void AMazeMonster::StopAttackSound()
{
	AttackAC->Stop();
}

#pragma endregion