// Copyright by 2026-1 WAP Game 2 team

#include "Character/AI/CryGhost/BT/BTT_FindPlayer.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <GameFramework/Character.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

EBTNodeResult::Type UBTT_FindPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto* Target = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto* BB = OwnerComp.GetBlackboardComponent();
	BB->SetValueAsObject(BlackboardKey.SelectedKeyName, Target);

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

#pragma endregion