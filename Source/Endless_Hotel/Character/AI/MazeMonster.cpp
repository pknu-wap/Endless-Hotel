// Copyright by 2025-2 WAP Game 2 team

#include "Character/AI/MazeMonster.h"
#include "Character/AI/MazeMonsterController.h"
#include "Character/Character/EHCharacter.h"
#include "MonsterAnimInstance.h"

AMazeMonster::AMazeMonster(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMazeMonster::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UMonsterAnimInstance* animInst = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	animInst->Speed = GetVelocity().Size2D();
}
