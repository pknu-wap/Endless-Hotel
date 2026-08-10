// Copyright by 2025-2 WAP Game 2 team

#include "Character/AI/MazeMonster/BT/BTTask_Attack.h"
#include "Character/AI/BaseAIAnimInstance.h"
#include "Player/Character/EHPlayer.h"
#include "Character/AI/MazeMonster/MazeMonsterController.h"
#include "Character/AI/MazeMonster/MazeMonster.h"
#include "Player/Controller/EHPlayerController.h"
#include <AIController.h>
#include <GameFramework/Character.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/CapsuleComponent.h>

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
	AMazeMonster* MazeMonster = Cast<AMazeMonster>(AIPawn);
	ACharacter* Character = Cast<ACharacter>(AIPawn);
	UBaseAIAnimInstance* AnimInst = Cast<UBaseAIAnimInstance>(Character->GetMesh()->GetAnimInstance());
	AnimInst->State = EAIAnimState::Attacking;


	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	UObject* TargetObject = BlackboardComp->GetValueAsObject(AMazeMonsterController::Key_TargetPlayer);

	AEHPlayer* Player = Cast<AEHPlayer>(TargetObject);
	if (!Player || MazeMonster->bIsAttacked) 
	{
		return EBTNodeResult::Failed;
	}

	MazeMonster->bIsAttacked = true;

	AEHPlayerController* PC = Cast<AEHPlayerController>(Player->GetController());
	PC->SetPlayerInputAble(false);

	FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
	MazeMonster->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MazeMonster->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	MazeMonster->GetCharacterMovement()->StopMovementImmediately(); 
	MazeMonster->GetMesh()->AttachToComponent(Player->GetMesh(), AttachRules, TEXT("JumpScare_MazeMonster"));
	MazeMonster->SetActorRelativeLocation(FVector::ZeroVector);
	MazeMonster->SetActorRelativeRotation(FRotator::ZeroRotator);
	MazeMonster->AttachAttackSoundTo(Player->GetMesh(), TEXT("JumpScare_MazeMonster"));
	MazeMonster->StopHeartbeatSound();
	MazeMonster->PlayAttackSound();

	FTimerHandle DelayHandle;
	GetWorld()->GetTimerManager().SetTimer(DelayHandle, FTimerDelegate::CreateWeakLambda(this, [this, Player, AIController, MazeMonster, &OwnerComp]()
		{
			AMazeMonsterController* BaseAIController = Cast<AMazeMonsterController>(AIController);
			BaseAIController->StopAI(TEXT("Attack"));
			Player->OnDie.Broadcast(EDeathReason::Attack);
			MazeMonster->StopAttackSound();
			MazeMonster->RestoreAttackSoundAttachment();
			MazeMonster->GetMesh()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}), DieDelay, false);

	return EBTNodeResult::InProgress;
}

#pragma endregion