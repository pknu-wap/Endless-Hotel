// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/CryGhost/Anomaly_CryGhost.h"
#include "Anomaly/Object/EightExit/Light/Anomaly_Object_Light.h"
#include "Character/AI/CryGhost/CryGhost.h"
#include "Player/Character/EHPlayer.h"
#include <Components/AudioComponent.h>
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Sound/SoundCue.h>

#pragma region Activity

void AAnomaly_CryGhost::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyID)
	{
	case EAnomalyID::CryGhost:
		TriggerBox->SetWorldTransform(CryTriggerTrans);
		ActiveTrigger();
		break;

	case EAnomalyID::CryGhost_Light:
		TriggerBox->SetWorldTransform(LightTriggerTrans);
		ActiveTrigger();
		break;
	}
}

void AAnomaly_CryGhost::DisableAnomaly()
{
	Super::DisableAnomaly();

	if (IsValid(CryGhost))
	{
		CryGhost->Destroy();
	}
}

#pragma endregion

#pragma region Trigger

void AAnomaly_CryGhost::OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEHPlayer* Player = Cast<AEHPlayer>(OtherActor);
	if (!IsValid(Player))
	{
		return;
	}

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	switch (AnomalyID)
	{
	case EAnomalyID::CryGhost:
		SpawnCryGhost(CrySpawnTrans);
		CryGhost->SetCryState();
		AdvanceCryGhostState();
		break;

	case EAnomalyID::CryGhost_Light:
		SpawnCryGhost(LightSpawnTrans);
		TurnAllLights(false);
		break;
	}
}

void AAnomaly_CryGhost::SpawnCryGhost(FTransform Trans)
{
	if (IsValid(CryGhost))
	{
		return;
	}

	CryGhost = GetWorld()->SpawnActor<ACryGhost>(GhostClass, Trans);
}

#pragma endregion

#pragma region Cry

void AAnomaly_CryGhost::AdvanceCryGhostState()
{
	switch (CryGhost->GetCurrentState())
	{
	case ECryGhostState::Cry:
	{
		CryGhost->PlayCrySound();
		TriggerBox->SetWorldTransform(StandTrans);

		constexpr float Delay = 0.1f;
		FTimerHandle DisableHandle;
		GetWorld()->GetTimerManager().SetTimer(DisableHandle, FTimerDelegate::CreateWeakLambda(this, [this]
			{
				TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			}), Delay, false);
		break;
	}
	case ECryGhostState::Stand:
	{
		CryGhost->PlayStandSound();
		TriggerBox->SetWorldTransform(JumpScareTrans);

		constexpr float Delay = 0.1f;
		FTimerHandle DisableHandle;
		GetWorld()->GetTimerManager().SetTimer(DisableHandle, FTimerDelegate::CreateWeakLambda(this, [this]
			{
				TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			}), Delay, false);
		break;
	}
	case ECryGhostState::JumpScare:
	{
		CryGhost->PlayJumpScareSound();

		constexpr float Delay = 1.33f;
		FTimerHandle DisableHandle;
		GetWorld()->GetTimerManager().SetTimer(DisableHandle, FTimerDelegate::CreateWeakLambda(this, [this]
			{
				CryGhost->Destroy();
			}), Delay, false);
		break;
	}
	}

	CryGhost->AdvanceCryGhostState();
}

#pragma endregion

#pragma region Light

void AAnomaly_CryGhost::TurnAllLights(bool bOn)
{
	for (AAnomaly_Object_Base* Target : TargetAnomalyObjects)
	{
		auto* Light = Cast<AAnomaly_Object_Light>(Target);
		Light->TurnLight(bOn);
	}

	if (bOn)
	{
		CryGhost->StopCryGhost();
	}
	else
	{
		PlayNoiseSound();
		CryGhost->RunCryGhost();
	}

	float TurnDuration = bOn ? 3.f : 1.5f;
	GetWorld()->GetTimerManager().SetTimer(LightHandle, FTimerDelegate::CreateUObject(this, &ThisClass::TurnAllLights, !bOn), TurnDuration, false);
}

void AAnomaly_CryGhost::PlayNoiseSound()
{
	AC_Light = UGameplayStatics::CreateSound2D(GetWorld(), SC_Noise);
	AC_Light->Play();
}

#pragma endregion