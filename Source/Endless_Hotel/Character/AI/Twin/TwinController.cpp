// Copyright by 2026-1 WAP Game 2 team

#include "Character/AI/Twin/TwinController.h"
#include "Twin.h"
#include "Player/Character/EHPlayer.h"
#include "Player/Controller/EHPlayerController.h"
#include <Kismet/GameplayStatics.h>

void ATwinController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AEHPlayer* Player = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	AEHPlayerController* PC = Cast<AEHPlayerController>(Player->Controller);
	ATwin* Twin = Cast<ATwin>(GetPawn());
	bool bObserved = PC->IsLookingAtActor(Twin, Twin->DetectDistance, false);
	ETwinState NewState = bObserved ? ETwinState::Frozen : ETwinState::Moving;

	Twin->SetTwinState(NewState);
	if (NewState == ETwinState::Moving)
	{
		MoveToActor(Player);
	}
}