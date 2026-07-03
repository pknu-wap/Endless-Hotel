// Copyright by 2025-2 WAP Game 2 team

#include "Character/AI/BaseAI.h"
#include "Character/AI/BaseAIController.h"
#include "Character/EHCharacter.h"
#include "Character/AI/BaseAIAnimInstance.h"

ABaseAI::ABaseAI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}