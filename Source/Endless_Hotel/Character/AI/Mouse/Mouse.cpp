// Copyright by 2026-1 WAP Game 2 team

#include "Character/AI/Mouse/Mouse.h"
#include "Character/AI/Mouse/MouseAnimInstance.h"

#pragma region Move

void AMouse::RunByEat()
{
	auto* AICon = Cast<AAIController>(GetController());
	AICon->ReceiveMoveCompleted.AddDynamic(this, &ThisClass::MoveToEatCompleted);
	AICon->MoveToLocation(EatDeadBodyLoc);
}

void AMouse::RunByJumpScare()
{
	auto* AnimInstance = Cast<UMouseAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->bIsRun = true;

	auto* AICon = Cast<AAIController>(GetController());
	AICon->ReceiveMoveCompleted.RemoveAll(this);
	AICon->ReceiveMoveCompleted.AddDynamic(this, &ThisClass::MoveToRunCompleted);
	AICon->MoveToLocation(RunLoc);
}

void AMouse::MoveToEatCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	auto* AnimInstance = Cast<UMouseAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->bIsRun = false;
}

void AMouse::MoveToRunCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	Destroy();
}

#pragma endregion