// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Neapolitan/BackChild/Anomaly_BackChild.h"
#include "Anomaly/Object/Neapolitan/BackChild/Anomaly_Object_BackChild.h"
#include "Player/Controller/EHPlayerController.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>

#pragma region BackChild

void AAnomaly_BackChild::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyName::BackChild:
		SetupAnomalyAction(&AAnomaly_Object_BackChild::AttatchChildToPlayer);
		ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		PlayerMC = Player->GetCharacterMovement();
		OriginalSpeed = PlayerMC->MaxWalkSpeed;
		ActiveTrigger();
		break;
	}
}

void AAnomaly_BackChild::DisableAnomaly()
{
	auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PC->bCanRun = true;
	PC->bCanCrouch = true;
	PlayerMC->MaxWalkSpeed = OriginalSpeed;
}

#pragma endregion