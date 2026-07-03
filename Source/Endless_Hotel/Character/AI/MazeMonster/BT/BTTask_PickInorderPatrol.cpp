// Copyright by 2025-2 WAP Game 2 team

#include "Character/AI/MazeMonster/BT/BTTask_PickInorderPatrol.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIController.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AI/MazeMonster/MazeMonsterController.h"
#include "Character/AI/MazeMonster/MazeMonster.h"

#pragma region Base

UBTTask_PickInorderPatrol::UBTTask_PickInorderPatrol()
{
	NodeName = TEXT("Pick Inorder Patrol");
}

void UBTTask_PickInorderPatrol::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	if (UBlackboardData* BBData = GetBlackboardAsset())
	{
		PatrolPosKey.ResolveSelectedKey(*BBData);
		LastIndexKey.ResolveSelectedKey(*BBData);
	}
}

#pragma endregion

#pragma region Task

EBTNodeResult::Type UBTTask_PickInorderPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AI = OwnerComp.GetAIOwner();
	AMazeMonster* Monster = Cast<AMazeMonster>(AI->GetPawn());

	const TArray<FTransform>& Points = Monster->PatrolPoints;
	if (Points.Num() == 0)
	{
		return EBTNodeResult::Failed;
	}
	FTransform Point = Points[Monster->CurrentIndex];
	Monster->CurrentIndex < (Points.Num() - 1) ? Monster->CurrentIndex++ : Monster->CurrentIndex = 0;

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	BB->SetValueAsVector(AMazeMonsterController::Key_PatrolPos, Point.GetLocation());

	return EBTNodeResult::Succeeded;
}

#pragma endregion