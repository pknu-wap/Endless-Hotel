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
	for (AMouse* Mouse : SpawnedMouse)
	{
		if (IsValid(Mouse))
		{
			Mouse->Destroy();
		}
	}

	if (IsValid(SpawnedDeadBody))
	{
		SpawnedDeadBody->Destroy();
	}

	SpawnedMouse.Empty();
	SpawnedDeadBody = nullptr;

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

	for (auto Info : MouseInfos)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnedMouse.Add(GetWorld()->SpawnActor<AMouse>(MouseClass, Info.SpawnLoc, FRotator::ZeroRotator, SpawnParams));
	}
	
	FTimerHandle RunHandle;
	GetWorld()->GetTimerManager().SetTimer(RunHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			for (int32 Index = 0; Index < SpawnedMouse.Num(); ++Index)
			{
				SpawnedMouse[Index]->RunByEat(MouseInfos[Index].EatLoc);
			}
		}), 1.f, false);

	TriggerBox->SetWorldTransform(JumpScareTrans);
	GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateWeakLambda(this, [this]() {TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly); }));
}

void AAnomaly_Event_Mouse::RunMouse()
{
	for (int32 Index = 0; Index < SpawnedMouse.Num(); ++Index)
	{
		FMouseInfo Info = MouseInfos[Index];
		AMouse* Mouse = SpawnedMouse[Index];
		Mouse->RunByJumpScare(Info.SpawnLoc);
	}
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