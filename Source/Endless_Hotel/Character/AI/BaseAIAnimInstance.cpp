// Copyright by 2025-2 WAP Game 2 team
#include "Character/AI/BaseAIAnimInstance.h"
#include "Character/AI/BaseAI.h"

void UBaseAIAnimInstance::OnStateAnimationEnds()
{
	if (State == EAIAnimState::Attacking)
	{
		State = EAIAnimState::Idle;
	}
	else
	{
		auto ownerActor = this->GetOwningActor();
		auto BaseAI = Cast<ABaseAI>(ownerActor);
		if (BaseAI == nullptr) return;
	}
}
