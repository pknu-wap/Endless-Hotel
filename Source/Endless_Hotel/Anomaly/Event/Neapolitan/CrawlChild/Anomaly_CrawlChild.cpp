// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Event/Neapolitan/CrawlChild/Anomaly_CrawlChild.h"
#include "Anomaly/Object/Neapolitan/CrawlChild/Anomaly_Object_CrawlChild.h"
#include "Anomaly/Object/EightExit/Door/Anomaly_Object_Door.h"
#include "Player/Controller/EHPlayerController.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>

#pragma region CrawlChild

void AAnomaly_CrawlChild::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyID::CrawlChild:
		SetupAnomalyAction(&AAnomaly_Object_CrawlChild::ActivePlayTrigger);
		SetupAnomalyAction(&AAnomaly_Object_Door::OpenDoor);
		ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		PlayerMC = Player->GetCharacterMovement();
		OriginalSpeed = PlayerMC->MaxWalkSpeed;
		ActiveTrigger();
		break;
	}
}

void AAnomaly_CrawlChild::DisableAnomaly()
{
	auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->bCanRun = true;
	PC->bCanCrouch = true;
	PlayerMC->MaxWalkSpeed = OriginalSpeed;
}

#pragma endregion