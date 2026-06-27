// Copyright by 2025-2 WAP Game 2 team

#include "Character/AI/BaseAIController.h"
#include "Character/EHCharacter.h"
#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <Perception/AIPerceptionComponent.h>
#include <Perception/AISenseConfig_Sight.h>
#include <Perception/AIPerceptionSystem.h>
#include <GameFramework/CharacterMovementComponent.h>

#pragma region Base

ABaseAIController::ABaseAIController(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
}

void ABaseAIController::ActiveAI()
{
	if (BrainComponent)
	{
		BrainComponent->RestartLogic();
	}
}

void ABaseAIController::DeActiveAI()
{
	if (BrainComponent)
	{
		BrainComponent->StartLogic();
	}
}

#pragma endregion

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* RawBB = nullptr;
	if (UseBlackboard(BBAsset, RawBB))
	{
		RunBehaviorTree(BTAsset);

		if (BrainComponent)
		{
			// 무슨 의도?
			//BrainComponent->StopLogic(TEXT("Wait for Activation"));
		}
	}
}