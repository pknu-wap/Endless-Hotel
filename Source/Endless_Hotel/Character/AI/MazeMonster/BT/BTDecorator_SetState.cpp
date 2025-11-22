// Copyright by 2025-2 WAP Game 2 team
#include "Character/AI/MazeMonster/BT/BTDecorator_SetState.h"
#include "Character/AI/MazeMonster/MazeMonsterAnimInstance.h"
#include "AIController.h"
#include "Character/AI/MazeMonster/MazeMonster.h"
#include "Components/SkeletalMeshComponent.h"

UBTDecorator_SetState::UBTDecorator_SetState()
{
	bNotifyActivation = true;
	bNotifyDeactivation = true;
}

UMazeMonsterAnimInstance* UBTDecorator_SetState::GetMonsterAnim(const FBehaviorTreeSearchData& SearchData)
{
	if (AAIController* MMCon = SearchData.OwnerComp.GetAIOwner())
	{
		if (APawn* Pawn = MMCon->GetPawn())
		{
			if (USkeletalMeshComponent* Mesh = Pawn->FindComponentByClass<USkeletalMeshComponent>())
				return Cast<UMazeMonsterAnimInstance>(Mesh->GetAnimInstance());
		}
	}
	return nullptr;
}

void UBTDecorator_SetState::OnNodeActivation(FBehaviorTreeSearchData& SearchData)
{
	if (UMazeMonsterAnimInstance* Anim = GetMonsterAnim(SearchData))
	{
		Anim->bIsMoving = bEntryIsMoving;
	}
}

void UBTDecorator_SetState::OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult)
{
	if (UMazeMonsterAnimInstance* Anim = GetMonsterAnim(SearchData))
	{
		Anim->bIsMoving = bOutIsMoving;
	}
}
