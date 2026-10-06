// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Event/EightExit/Mouse/Anomaly_Event_Mouse.h"
#include "Character/AI/Mouse/Mouse.h"
#include "Player/Character/EHPlayer.h"
#include <Animation/SkeletalMeshActor.h>
#include <Components/BoxComponent.h>

#pragma region Activity

void AAnomaly_Event_Mouse::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyID)
	{
	case EAnomalyID::Mouse:
		SpawnDeadBody();
		ActiveTrigger();
		break;
	}
}

void AAnomaly_Event_Mouse::DisableAnomaly()
{
	if (IsValid(SpawnedMouse))
	{
		SpawnedMouse->Destroy();
	}

	if (IsValid(SpawnedDeadBody))
	{
		SpawnedDeadBody->Destroy();
	}

	Super::DisableAnomaly();
}

#pragma endregion

#pragma region Trigger

void AAnomaly_Event_Mouse::OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto* Player = Cast<AEHPlayer>(OtherActor);
	if (!IsValid(Player))
	{
		return;
	}

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (!bSpawnedMouse)
	{
		SpawnMouse();
		return;
	}

	RunMouse();
	JumpScareDeadBody();
}

#pragma endregion

#pragma region Mouse

void AAnomaly_Event_Mouse::SpawnMouse()
{
	bSpawnedMouse = true;

	SpawnedMouse = GetWorld()->SpawnActor<AMouse>(MouseClass, SpawnMouseTrans);
	
	FTimerHandle RunHandle;
	GetWorld()->GetTimerManager().SetTimer(RunHandle, FTimerDelegate::CreateWeakLambda(this, [this]() {SpawnedMouse->RunByEat(); }), 1.f, false);

	TriggerBox->SetWorldTransform(JumpScareTrans);
	GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateWeakLambda(this, [this]() {TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly); }));
}

void AAnomaly_Event_Mouse::RunMouse()
{
	SpawnedMouse->RunByJumpScare();
}

#pragma endregion

#pragma region DeadBody

void AAnomaly_Event_Mouse::SpawnDeadBody()
{
	SpawnedDeadBody = GetWorld()->SpawnActor<ASkeletalMeshActor>(DeadBodyClass, SpawnDeadBodyTrans);
}

void AAnomaly_Event_Mouse::JumpScareDeadBody()
{
	auto* Mesh = SpawnedDeadBody->GetSkeletalMeshComponent();
	auto* AnimInstance = Mesh->GetAnimInstance();
	AnimInstance->Montage_Play(AM_JumpScare);
}

#pragma endregion