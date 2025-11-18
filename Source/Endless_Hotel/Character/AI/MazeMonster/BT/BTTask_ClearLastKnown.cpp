// Copyright by 2025-2 WAP Game 2 team

#include "Character/AI/MazeMonster/BT/BTTask_ClearLastKnown.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AI/MazeMonster/MazeMonsterController.h"

#pragma region Base

UBTTask_ClearLastKnown::UBTTask_ClearLastKnown()
{
	NodeName = TEXT("Clear LastKnownPos");
}

#pragma endregion

#pragma region Task

EBTNodeResult::Type UBTTask_ClearLastKnown::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent())
	{
		BlackboardComp->ClearValue(AMazeMonsterController::Key_LastKnownPos);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

#pragma endregion