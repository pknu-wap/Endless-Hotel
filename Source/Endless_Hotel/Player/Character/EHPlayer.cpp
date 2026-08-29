// Copyright by 2025-2 WAP Game 2 team

#include "Player/Character/EHPlayer.h"
#include "Player/Controller/EHPlayerController.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include <Components/PointLightComponent.h>
#include <Camera/CameraComponent.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>

#pragma region Base

AEHPlayer::AEHPlayer(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetMesh(), TEXT("HeadSocket"));
	Camera->bUsePawnControlRotation = true;

	Lighter = CreateDefaultSubobject<UPointLightComponent>(TEXT("Lighter"));
	Lighter->SetVisibility(false);
	Lighter->SetupAttachment(GetMesh());

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	OnDie.AddUObject(this, &ThisClass::DiePlayer);
}

void AEHPlayer::BeginPlay()
{
	Super::BeginPlay();

	RevivePlayer();
}

#pragma endregion

#pragma region Movement

void AEHPlayer::SetWalkSpeed(float Value)
{
	GetCharacterMovement()->MaxWalkSpeed = Value;
}

#pragma endregion

#pragma region Spawn

void AEHPlayer::RespawnPlayer()
{
	FTransform TargetTrans;

	switch (USaveManager::LoadData_Progression().Progression)
	{
	case EGameProgression::CheckIn:
		TargetTrans = SpawnTransform[EGameProgression::CheckIn];
		break;

	case EGameProgression::Tutorial:
		TargetTrans = SpawnTransform[EGameProgression::Tutorial];
		break;

	case EGameProgression::Loop:
		TargetTrans = SpawnTransform[EGameProgression::Loop];
		break;
	}

	SetActorTransform(TargetTrans);
	GetController()->SetControlRotation(TargetTrans.Rotator());
}

#pragma endregion

#pragma region Die & Revive

void AEHPlayer::DiePlayer(const EDeathReason& DeathReason)
{
	bIsDead = true;

	UAnimMontage* AM_Die = DieMontage[DeathReason];
	const float AnimLength = AM_Die->GetPlayLength();
	PlayAnimMontage(AM_Die);

	Camera->bUsePawnControlRotation = false;

	GetMesh()->bNoSkeletonUpdate = true;

	auto* VerdictSub = GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>();
	VerdictSub->bIsStartInBed = true;
	VerdictSub->ApplyVerdict();

	constexpr float ReviveDuration = 6.f;
	FTimerHandle DeathHandle;
	GetWorld()->GetTimerManager().SetTimer(DeathHandle, this, &ThisClass::RevivePlayer, AnimLength + ReviveDuration, false);
}

void AEHPlayer::RevivePlayer()
{
	bIsDead = false;

	RespawnPlayer();
	SetWalkSpeed(WALK_SPEED);
	
	Camera->bUsePawnControlRotation = true;

	OnRevive.Broadcast();
}

#pragma endregion