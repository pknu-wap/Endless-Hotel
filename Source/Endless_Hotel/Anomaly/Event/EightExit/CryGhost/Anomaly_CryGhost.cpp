// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/CryGhost/Anomaly_CryGhost.h"
#include "Character/AI/CryGhost/CryGhost.h"
#include "Player/Character/EHPlayer.h"
#include <Components/BoxComponent.h>

#pragma region Activity

void AAnomaly_CryGhost::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyID::CryGhost:
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

	if (!IsValid(CryGhost))
	{
		CryGhost = GetWorld()->SpawnActor<ACryGhost>(GhostClass, GhostSpawnTrans);
	}
	else
	{
		CryGhost->AdvanceCryGhostState();
	}

	switch (CryGhost->GetCurrentState())
	{
	case ECryGhostState::Cry:
	{
		CryGhost->PlayCrySound();
		TriggerBox->SetWorldTransform(StandTrans);

		FTimerHandle DisableHandle;
		GetWorld()->GetTimerManager().SetTimer(DisableHandle, FTimerDelegate::CreateWeakLambda(this, [this]
			{
				TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			}), 0.1f, false);

		break;
	}
	case ECryGhostState::Stand:
	{
		CryGhost->PlayStandSound();
		TriggerBox->SetWorldTransform(JumpScareTrans);

		FTimerHandle DisableHandle;
		GetWorld()->GetTimerManager().SetTimer(DisableHandle, FTimerDelegate::CreateWeakLambda(this, [this]
			{
				TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			}), 0.1f, false);

		break;
	}
	case ECryGhostState::JumpScare:
	{
		CryGhost->PlayJumpScareSound();

		FTimerHandle DisableHandle;
		GetWorld()->GetTimerManager().SetTimer(DisableHandle, FTimerDelegate::CreateWeakLambda(this, [this]
			{
				CryGhost->Destroy();
			}), 0.1f, false);

		break;
	}
	}
}

#pragma endregion