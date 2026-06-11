// Copyright by 2026-1 WAP Game 2 team

#include "Character/AI/CryGhost/CryGhost.h"
#include "Character/AI/CryGhost/CryGhostAnimInstance.h"
#include <Components/AudioComponent.h>

#pragma region Base

ACryGhost::ACryGhost(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->SetAutoActivate(false);
	AudioComponent->OnAudioFinished.AddDynamic(this, &ThisClass::PlayCrySound);
}

#pragma endregion

#pragma region State

void ACryGhost::AdvanceCryGhostState()
{
	++CurrentState;

	auto* AnimInstance = Cast<UCryGhostAnimInstance>(GetMesh()->GetAnimInstance());
	
	switch (CurrentState)
	{
	case ECryGhostState::Stand:
		AnimInstance->bIsStand = true;
		break;

	case ECryGhostState::JumpScare:
		AnimInstance->bIsJumpScare = true;
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