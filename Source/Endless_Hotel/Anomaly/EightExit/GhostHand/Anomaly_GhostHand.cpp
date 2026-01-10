// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/GhostHand/Anomaly_GhostHand.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/Controller/EHPlayerController.h"
#include "TimerManager.h"

#pragma region Base

AAnomaly_GhostHand::AAnomaly_GhostHand(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	SM_Hand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Hand"));
	SM_Hand->SetupAttachment(RootComponent);
	SM_Hand->SetVisibility(false);
	SM_Hand->SetHiddenInGame(true);
	SM_Hand->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAnomaly_GhostHand::BeginPlay()
{
	Super::BeginPlay();
}

void AAnomaly_GhostHand::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ClearRunLock();
	Super::EndPlay(EndPlayReason);
}
#pragma endregion

#pragma region Activity
void AAnomaly_GhostHand::ActivateAnomaly()
{
	Super::ActivateAnomaly();
	ExecuteGhostHand();
}
#pragma endregion

#pragma region GhostHand
void AAnomaly_GhostHand::ExecuteGhostHand()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Player)
	{
		return;
	}

	USkeletalMeshComponent* PlayerMesh = Player->GetMesh();
	if (!PlayerMesh)
	{
		return;
	}

	const FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, true);
	SM_Hand->AttachToComponent(PlayerMesh, Rules, AttachSocketName);

	SM_Hand->SetRelativeLocation(AttachLocationOffset);
	SM_Hand->SetRelativeRotation(AttachRotationOffset);
	SM_Hand->SetRelativeScale3D(AttachScale);

	SM_Hand->SetHiddenInGame(false);
	SM_Hand->SetVisibility(true);

	if(bLockRun)
	{
		ApplyRunLock();
	}
}
#pragma endregion

#pragma region RunLock
void AAnomaly_GhostHand::ApplyRunLock()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Player)
	{
		return;
	}
	if (AEHPlayerController* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0)))
	{
		if (!bSaved)
		{
			SavedCanRun = PC->bCanRun;
		}
		PC->bCanRun = false;
	}
	UCharacterMovementComponent* Move = Player->GetCharacterMovement();
	if (!Move)
	{
		return;
	}
	if (!bSaved)
	{
		SavedMaxWalkSpeed = Move->MaxWalkSpeed;
		bSaved = true;
	}

	Move->MaxWalkSpeed = LockedWalkSpeed;

	GetWorld()->GetTimerManager().ClearTimer(ReapplySpeedHandle);
	GetWorld()->GetTimerManager().SetTimer(ReapplySpeedHandle, FTimerDelegate::CreateLambda([this]()
		{
			ACharacter* P = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			if (!P)
			{
				return;
			}

			if (UCharacterMovementComponent* M = P->GetCharacterMovement())
			{
				M->MaxWalkSpeed = LockedWalkSpeed;
			}
		}), ReapplyInterval, true);
}

void AAnomaly_GhostHand::ClearRunLock()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(ReapplySpeedHandle);
	}

	if (bSaved)
	{
		if (ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			if (UCharacterMovementComponent* Move = Player->GetCharacterMovement())
			{
				Move->MaxWalkSpeed = SavedMaxWalkSpeed;
			}
		}
		bSaved = false;
	}
	if (AEHPlayerController* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		PC->bCanRun = SavedCanRun;
	}
}
#pragma endregion
