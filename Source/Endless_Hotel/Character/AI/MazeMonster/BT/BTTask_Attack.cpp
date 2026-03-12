#include "Character/AI/MazeMonster/BT/BTTask_Attack.h"
#include "Character/AI/BaseAIAnimInstance.h"
#include "Player/Character/EHPlayer.h"
#include "Character/AI/MazeMonster/MazeMonsterController.h"
#include <AIController.h>
#include <GameFramework/Character.h>
#include <BehaviorTree/BlackboardComponent.h>

#pragma region Base

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("MazeMonster Attack");
}

#pragma endregion

#pragma region Task

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* AIPawn = AIController->GetPawn();
	ACharacter* Character = Cast<ACharacter>(AIPawn);
	UBaseAIAnimInstance* AnimInst = Cast<UBaseAIAnimInstance>(Character->GetMesh()->GetAnimInstance());
	AnimInst->State = EAIAnimState::Attacking;


	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	UObject* TargetObject = BlackboardComp->GetValueAsObject(AMazeMonsterController::Key_TargetPlayer);

	AEHPlayer* Player = Cast<AEHPlayer>(TargetObject);
	if (Player && !Player->bIsDead) return EBTNodeResult::Failed;

	Player->DieDelegate.Broadcast(EDeathReason::Attack);

	return EBTNodeResult::Succeeded;
}

#pragma endregion

