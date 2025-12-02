// Copyright by 2025-2 WAP Game 2 team

#include "Character/AI/MazeMonster/BT/BTDecorator_CheckAttack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTDecorator_CheckAttack::UBTDecorator_CheckAttack()
{
	NodeName = TEXT("Check Attack Range");
}

bool UBTDecorator_CheckAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AAIController* AICon = OwnerComp.GetAIOwner();
	if (!AICon) return false;
	APawn* AIPawn = AICon->GetPawn();
	if (!AIPawn) return false;
	AActor* TargetActor = nullptr;

	if (TargetKey.SelectedKeyType != nullptr)
	{
		if (UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent())
		{
			UObject* Value = BB->GetValueAsObject(TargetKey.SelectedKeyName);
			TargetActor = Cast<AActor>(Value);
		}
	}
	if (!TargetActor) return false;
	const float DistSq = FVector::DistSquared(AIPawn->GetActorLocation(),TargetActor->GetActorLocation());
	const float AttackRangeSq = AttackRange * AttackRange;
	return DistSq <= AttackRangeSq;
}
