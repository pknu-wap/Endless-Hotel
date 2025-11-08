// Copyright by 2025-2 WAP Game 2 team


#include "Character/AI/BTTask_MoveToLastKnown.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "Character/AI/MazeMonsterController.h"

#pragma region Base

UBTTask_MoveToLastKnown::UBTTask_MoveToLastKnown()
{
	NodeName = TEXT("Set PatrolPos Around LastKnown");
}

#pragma endregion

#pragma region Task

EBTNodeResult::Type UBTTask_MoveToLastKnown::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();
	if (!BlackBoard) return EBTNodeResult::Failed;

	const FVector Base = BlackBoard->GetValueAsVector(AMazeMonsterController::Key_LastKnownPos);
	if (!Base.IsNearlyZero(1e-3))
	{
		FVector Dest = Base + FVector(
			FMath::FRandRange(-SearchRadius, SearchRadius),
			FMath::FRandRange(-SearchRadius, SearchRadius),
			0.f);

		if (bProjectToNavMesh)
		{
			if (const UNavigationSystemV1* Nav = FNavigationSystem::GetCurrent<UNavigationSystemV1>(OwnerComp.GetWorld()))
			{
				FNavLocation ProjectedLoc;
				if (Nav->ProjectPointToNavigation(Dest, ProjectedLoc, FVector(SearchRadius)))
				{
					BlackBoard->SetValueAsVector(AMazeMonsterController::Key_PatrolPos, ProjectedLoc.Location);
					return EBTNodeResult::Succeeded;
				}
				else if (bFailIfUnreachable)
				{
					return EBTNodeResult::Failed;
				}
			}
		}

		BlackBoard->SetValueAsVector(AMazeMonsterController::Key_PatrolPos, Dest);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

#pragma endregion