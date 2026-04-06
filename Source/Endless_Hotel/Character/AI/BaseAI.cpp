// Copyright by 2025-2 WAP Game 2 team

#include "Character/AI/BaseAI.h"
#include "Character/AI/BaseAIController.h"
#include "Character/Character/EHCharacter.h"
#include "BaseAIAnimInstance.h"

ABaseAI::ABaseAI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABaseAI::ActivateMob()
{
    ABaseAIController* AIC = Cast<ABaseAIController>(GetController());
    if (AIC)
    {
        AIC->ActiveAI();
    }
}

void ABaseAI::DeActivateMob()
{
    ABaseAIController* AIC = Cast<ABaseAIController>(GetController());
    if (AIC)
    {
        AIC->DeActiveAI();
    }
}
