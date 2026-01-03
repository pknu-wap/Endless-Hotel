// Copyright by 2025-2 WAP Game 2 team

#include "GameSystem/SubSystem/UHotelWorldSubsystem.h"
#include "AnomalyProgressSubSystem.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>

void UUHotelWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	UAnomalyProgressSubSystem* Progress = InWorld.GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
	if (ACharacter* Player = UGameplayStatics::GetPlayerCharacter(&InWorld, 0))
	{
		if (!Progress->bPassed) Player->SetActorLocation(PlayerStartLocation);
	}
}
