// Copyright by 2026-1 WAP Game 2 team

#include "Character/AI/CryGhost/CryGhost.h"
#include "Character/AI/CryGhost/CryGhostAnimInstance.h"
#include "Character/AI/CryGhost/CryGhostController.h"
#include "Player/Character/EHPlayer.h"
#include <Components/AudioComponent.h>
#include <Components/CapsuleComponent.h>
#include <Kismet/GameplayStatics.h>
#include <GameFramework/CharacterMovementComponent.h>

#pragma region Base

ACryGhost::ACryGhost(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->SetAutoActivate(false);
	AudioComponent->OnAudioFinished.AddDynamic(this, &ThisClass::PlayCrySound);

	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	DeathTrigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("DeathTrigger"));
	DeathTrigger->SetupAttachment(GetMesh());
	DeathTrigger->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnDeathTrigger);
}

#pragma endregion

#pragma region State

void ACryGhost::SetCryState()
{
	auto* AnimInstance = Cast<UCryGhostAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->bIsCry = true;

	GetController<ACryGhostController>()->StopAI(TEXT("Don't Move!!!"));

	DeathTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACryGhost::AdvanceCryGhostState()
{
	auto* AnimInstance = Cast<UCryGhostAnimInstance>(GetMesh()->GetAnimInstance());
	
	switch (CurrentState++)
	{
	case ECryGhostState::Stand:
		AnimInstance->bIsStand = true;
		break;

	case ECryGhostState::JumpScare:
		AnimInstance->bIsJumpScare = true;
		UWorld* World = GetWorld();
		TargetPlayer = UGameplayStatics::GetPlayerCharacter(World, 0);
		World->GetTimerManager().SetTimer(TargetingHandle, this, &ThisClass::AdjustGhostRotation, World->GetDeltaSeconds(), true);
		break;
	}
}

#pragma endregion

#pragma region Sound

void ACryGhost::PlayCrySound()
{
	if (CurrentState != ECryGhostState::Cry)
	{
		AudioComponent->OnAudioFinished.Clear();
		AudioComponent->Stop();
		return;
	}

	PlaySound(SW_Cry);
}

void ACryGhost::PlayStandSound()
{
	AudioComponent->OnAudioFinished.Clear();
	PlaySound(SW_Stand);
}

void ACryGhost::PlayJumpScareSound()
{
	PlaySound(SW_JumpScare);
}

void ACryGhost::PlaySound(USoundWave* SoundWave)
{
	AudioComponent->Stop();
	AudioComponent->SetSound(SoundWave);
	AudioComponent->Play();
}

#pragma endregion

#pragma region Targeting

void ACryGhost::AdjustGhostRotation()
{
	FVector Direction = TargetPlayer->GetActorLocation() - GetActorLocation();
	Direction.Z = 0.f;

	FRotator TargetRotator = Direction.Rotation();

	SetActorRotation(TargetRotator);
}

#pragma endregion

#pragma region Run

void ACryGhost::RunCryGhost()
{
	DeathTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	PlayAnimMontage(AM_Run);

	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

void ACryGhost::StopCryGhost()
{
	GetCharacterMovement()->MaxWalkSpeed = 0.f;
}

#pragma endregion

#pragma region Death

void ACryGhost::OnDeathTrigger(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto* Player = Cast<AEHPlayer>(OtherActor))
	{
		Player->DieDelegate.Broadcast(EDeathReason::Attack);
		DeathTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

#pragma endregion