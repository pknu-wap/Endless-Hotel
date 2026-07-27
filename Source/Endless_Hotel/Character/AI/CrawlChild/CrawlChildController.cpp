// Copyright by 2026-1 WAP Game 2 team

#include "Character/AI/CrawlChild/CrawlChildController.h"
#include "CrawlChild.h"
#include "Player/Character/EHPlayer.h"
#include <Kismet/GameplayStatics.h>

#pragma region PlayAnimation

void ACrawlChildController::FallFromWheelChair()
{
	APawn* AIPawn = GetPawn();
	//ToDo: 휠체어에서 떨어지는 연출
	AEHPlayer* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FTimerHandle DelayHandle;
	GetWorld()->GetTimerManager().SetTimer(DelayHandle, FTimerDelegate::CreateWeakLambda(this, [this, Player]()
		{
			MoveToActor(Player);
		}), AnimationLengths[0], false);
}

#pragma endregion