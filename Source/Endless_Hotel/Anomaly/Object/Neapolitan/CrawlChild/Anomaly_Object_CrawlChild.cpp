// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/CrawlChild/Anomaly_Object_CrawlChild.h"
#include "Player/Controller/EHPlayerController.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>

#pragma region CrawlChild

void AAnomaly_Object_CrawlChild::AttatchChildToPlayer()
{
	bSolved = true;
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	USkeletalMeshComponent* PlayerMesh = PlayerCharacter->GetMesh();
	UCharacterMovementComponent* Move = PlayerCharacter->GetCharacterMovement();
	AEHPlayerController* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	const FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
	this->AttachToComponent(PlayerMesh, AttachRules, SocketName);

	PC->bCanRun = false;
	PC->bIsRunning = false;
	PC->bCanCrouch = false;
	Move->MaxWalkSpeed = LockSpeed;
}

#pragma endregion