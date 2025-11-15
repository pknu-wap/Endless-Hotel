// Copyright by 2025-2 WAP Game 2 team
#include "Character/AI/MonsterAnimInstance.h"
#include "Character/AI/MazeMonster.h"

void UMonsterAnimInstance::OnStateAnimationEnds()
{
	if (State == EMonsterAnimState::Attacking)
	{
		State = EMonsterAnimState::Locomotion;
	}
	else
	{
		auto ownerActor = this->GetOwningActor();
		auto mazeMonster = Cast<AMazeMonster>(ownerActor);
		if (mazeMonster == nullptr) return;
	}
}
