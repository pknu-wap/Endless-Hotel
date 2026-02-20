// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/GhostHand/Anomaly_GhostHand.h"
#include "Player/Controller/EHPlayerController.h"
#include <Components/StaticMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>
#include <Components/SkeletalMeshComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

#pragma region Base
AAnomaly_GhostHand::AAnomaly_GhostHand(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SM_Hand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Hand"));
	SM_Hand->SetupAttachment(RootComponent);

	SM_Hand->SetVisibility(false);
}
#pragma endregion

#pragma region Activity

void AAnomaly_GhostHand::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();
	
	switch (AnomalyName)
	{
	case EAnomalyName::GhostHand:
			AttachGhostHand();
			ScheduleAnomaly();
			break;
	}
}
#pragma endregion

#pragma region GhostHand
void AAnomaly_GhostHand::AttachGhostHand()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	USkeletalMeshComponent* PlayerMesh = PlayerCharacter->GetMesh();
	UCharacterMovementComponent* Move = PlayerCharacter->GetCharacterMovement();

	const FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
	SM_Hand->AttachToComponent(PlayerMesh, AttachRules, AttachSoketName);

	SM_Hand->SetVisibility(true);

	if (bLockRun)
	{
		if (AEHPlayerController* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
		{
			PC->bCanRun = false;
		}
		Move->MaxWalkSpeed = LockWalkSpeed;
		GetWorld()->GetTimerManager().ClearTimer(ReapplySpeedHandle);
		GetWorld()->GetTimerManager().SetTimer(ReapplySpeedHandle, FTimerDelegate::CreateWeakLambda(this, [this, Move]()
			{
				Move->MaxWalkSpeed = LockWalkSpeed;
			}), ReapplyInterval, true);
	}
}