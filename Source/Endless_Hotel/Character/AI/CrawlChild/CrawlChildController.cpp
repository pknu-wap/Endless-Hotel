// Copyright by 2026-1 WAP Game 2 team

#include "Character/AI/CrawlChild/CrawlChildController.h"
#include "CrawlChild.h"
#include "CrawlChildAnimInstance.h"
#include "Anomaly/Object/EightExit/CrawlChild/AAnomaly_Object_WChair.h"
#include "Player/Character/EHPlayer.h"
#include <GameFrameWork/CharacterMovementComponent.h>
#include <Kismet/GameplayStatics.h>

#pragma region PlayAnimation

void ACrawlChildController::StartWithWheelChair()
{
	CrawlChild = Cast<ACrawlChild>(GetPawn());
	CrawlChild->GetCharacterMovement()->DisableMovement();
	CrawlChild->SetActorEnableCollision(false);
	const FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
	CrawlChild->AttachToComponent(CrawlChild->WheelChairObjectRef->GetRootComponent(), AttachRules, NAME_None);
	CrawlChild->SetActorRelativeLocation(SeatOffsetTransform.GetLocation());
	CrawlChild->SetActorRelativeRotation(SeatOffsetTransform.GetRotation());

	auto* AnimInst = Cast<UCrawlChildAnimInstance>(CrawlChild->GetMesh()->GetAnimInstance());
	AnimInst->bIsRiding = true;
	
	FTimerHandle DelayHandle;
	GetWorld()->GetTimerManager().SetTimer(DelayHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			FallFromWheelChair();
		}), AnimationLengths[0], false);
}

void ACrawlChildController::FallFromWheelChair()
{
	//ToDo: 휠체어에서 떨어지는 연출
	auto* AnimInst = Cast<UCrawlChildAnimInstance>(CrawlChild->GetMesh()->GetAnimInstance());
	AnimInst->bIsRiding = false;

	const FDetachmentTransformRules DetachRules(EDetachmentRule::KeepWorld, true);
	CrawlChild->DetachFromActor(DetachRules);
	CrawlChild->SetActorEnableCollision(true);
	CrawlChild->GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	AEHPlayer* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FTimerHandle DelayHandle;
	GetWorld()->GetTimerManager().SetTimer(DelayHandle, FTimerDelegate::CreateWeakLambda(this, [this, Player, AnimInst]()
		{
			MoveToActor(Player);
			AnimInst->bIsCrawling = true;
		}), AnimationLengths[1], false);
}

#pragma endregion