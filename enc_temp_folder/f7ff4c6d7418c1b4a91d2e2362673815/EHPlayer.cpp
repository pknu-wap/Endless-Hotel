// Copyright by 2025-2 WAP Game 2 team

#include "Player/Character/EHPlayer.h"
#include "Player/Camera/EHPlayerCameraManager.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include <Components/AudioComponent.h>
#include <Components/PointLightComponent.h>
#include <Camera/CameraComponent.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>

#pragma region Base

AEHPlayer::AEHPlayer(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh(), TEXT("HeadSocket"));
	SpringArm->TargetArmLength = 20.0f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	HeartbeatAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("HeartbeatAudioComponent"));
	HeartbeatAudioComponent->SetupAttachment(RootComponent);
	HeartbeatAudioComponent->bAutoActivate = false;

	ElevatorMoveAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ElevatorMoveAudioComponent"));
	ElevatorMoveAudioComponent->SetupAttachment(RootComponent);
	ElevatorMoveAudioComponent->bAutoActivate = false;

	Lighter = CreateDefaultSubobject<UPointLightComponent>(TEXT("Lighter"));
	Lighter->SetVisibility(false);
	Lighter->SetupAttachment(GetMesh());

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	OnDie.AddUObject(this, &ThisClass::DiePlayer);
}

void AEHPlayer::BeginPlay()
{
	Super::BeginPlay();

	RespawnPlayer();
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
	switch (USaveManager::LoadData_Progression().Progression)
	{
	case EGameProgression::CheckIn:
		SetActorTransform(SpawnTransform[EGameProgression::CheckIn]);
		break;

	case EGameProgression::Tutorial:
		SetActorTransform(SpawnTransform[EGameProgression::Tutorial]);
		break;

	case EGameProgression::Loop:
		SetActorTransform(SpawnTransform[EGameProgression::Loop]);
		break;
	}
}

#pragma endregion

#pragma region Die & Revive

void AEHPlayer::DiePlayer(const EDeathReason& DeathReason)
{
	bIsDead = true;

	UAnimMontage* AM_Die = DieMontage[DeathReason];
	const float AnimLength = AM_Die->GetPlayLength();
	PlayAnimMontage(AM_Die);

	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 20.0f;

	GetMesh()->bNoSkeletonUpdate = true;

	auto* SubSystem = GetGameInstance()->GetSubsystem<UGameSystem>();
	SubSystem->ApplyVerdict();

	FTimerHandle EyeHandle;
	GetWorld()->GetTimerManager().SetTimer(EyeHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			auto* CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
			CameraManager->StartEyeEffect(false);
		}), AnimLength, false);

	constexpr float ReviveDuration = 6.f;
	FTimerHandle DeathHandle;
	GetWorld()->GetTimerManager().SetTimer(DeathHandle, this, &ThisClass::RevivePlayer, AnimLength + ReviveDuration, false);
}

void AEHPlayer::RevivePlayer()
{
	bIsDead = false;

	RespawnPlayer();
	SetWalkSpeed(WALK_SPEED);

	auto* CameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	CameraManager->StartEyeEffect(true);

	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bEnableCameraRotationLag = false;

	OnRevive.Broadcast();
}

#pragma endregion

#pragma region Sound

void AEHPlayer::PlayElevatorSound(bool bIsPlay)
{
	bIsPlay ? ElevatorMoveAudioComponent->Play() : ElevatorMoveAudioComponent->Stop();
}

#pragma endregion