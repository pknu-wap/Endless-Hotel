// Copyright by 2025-2 WAP Game 2 team

#include "Character/AI/BT/BTTask_PickRandomPatrol.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIController.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AI/MazeMonsterController.h"
#include "Character/AI/MazeMonster.h"

#pragma region Base

UBTTask_PickRandomPatrol::UBTTask_PickRandomPatrol()
{
	NodeName = TEXT("Pick Random Patrol");
}

void UBTTask_PickRandomPatrol::InitializeFromAsset(UBehaviorTree& Asset)
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

EBTNodeResult::Type UBTTask_PickRandomPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AI = OwnerComp.GetAIOwner();
	if (!AI) return EBTNodeResult::Failed;

	AMazeMonster* Monster = Cast<AMazeMonster>(AI->GetPawn());
	if (!Monster) return EBTNodeResult::Failed;

	const TArray<TObjectPtr<AActor>>& Points = Monster->PatrolPoints;
	if (Points.Num() == 0) return EBTNodeResult::Failed;

	const int32 RandomIndex = FMath::RandRange(0, Points.Num() - 1);
	AActor* Point = Points[RandomIndex];
	if (!Point) return EBTNodeResult::Failed;

	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	BB->SetValueAsVector(AMazeMonsterController::Key_PatrolPos, Point->GetActorLocation());

	return EBTNodeResult::Succeeded;
}

#pragma endregion