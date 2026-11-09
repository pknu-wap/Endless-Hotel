// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Wind-up/Anomaly_Object_Windup.h"
#include "Component/Interact/BurnComponent.h"
#include <Niagara/Public/NiagaraComponent.h>

#pragma region Base

AAnomaly_Object_Windup::AAnomaly_Object_Windup(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SKM_Windup = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKM_Windup"));
	SKM_Windup->SetupAttachment(RootComponent);
}

#pragma endregion

#pragma region Reset

void AAnomaly_Object_Windup::InitializeOnAnomalySpawned()
{
	Super::InitializeOnAnomalySpawned();

	CurrentInteractStep = EWindupInteractStep::NeedStopSound;

	auto& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(DelayHandle);
	TimerManager.ClearTimer(WindupPlayHandle);

	CurrentWindupPlayCount = 0;

	if (UAnimInstance* AnimInstance = SKM_Windup->GetAnimInstance())
	{
		AnimInstance->Montage_Stop(0.f);
	}

	SKM_Windup->SetHiddenInGame(true);
	SKM_Windup->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SKM_Windup->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);

	Object->SetHiddenInGame(true);
	Object->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Object->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
}

#pragma endregion

#pragma region Set

void AAnomaly_Object_Windup::SetWindup()
{
	SKM_Windup->SetHiddenInGame(false);
	SKM_Windup->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SKM_Windup->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	Object->SetHiddenInGame(false);
	Object->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Object->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	GetWorld()->GetTimerManager().SetTimer(DelayHandle, this, &ThisClass::StartWindupLoop, 10.f, false);
}

#pragma endregion

#pragma region Sound

void AAnomaly_Object_Windup::StartWindupLoop()
{
	CurrentWindupPlayCount = 0;

	WindupLoopTick();

	GetWorld()->GetTimerManager().SetTimer(WindupPlayHandle, this, &ThisClass::WindupLoopTick, WindupPlayInterval, true);
}

void AAnomaly_Object_Windup::WindupLoopTick()
{
	if (CurrentWindupPlayCount >= MaxWindupPlayCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(WindupPlayHandle);
		return;
	}
	WindupPlay();
	CurrentWindupPlayCount++;
}

void AAnomaly_Object_Windup::WindupPlay()
{
	PlayWindupAnimation();
}

void AAnomaly_Object_Windup::StopWindup()
{
	GetWorld()->GetTimerManager().ClearTimer(WindupPlayHandle);

	SKM_Windup->Stop();
}

void AAnomaly_Object_Windup::StartWrongLoop()
{
	GetWorld()->GetTimerManager().ClearTimer(WindupPlayHandle);
	SKM_Windup->Stop();
	PlayWrongMontage();
}

#pragma endregion

#pragma region Animation

void AAnomaly_Object_Windup::PlayWindupAnimation()
{
	SKM_Windup->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	SKM_Windup->SetAnimation(WindupAnimation);
	SKM_Windup->SetPosition(0.0f, false);
	SKM_Windup->Play(false);
}

void AAnomaly_Object_Windup::PlayWrongMontage()
{
	SKM_Windup->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	UAnimInstance* AnimInstance = SKM_Windup->GetAnimInstance();

	AnimInstance->PlaySlotAnimationAsDynamicMontage(WrongWindupAnimation, TEXT("DefaultSlot"), 0.f, 0.f, 1.f, WrongPlayCount);
}

#pragma endregion

#pragma region Burn

void AAnomaly_Object_Windup::StartBurning()
{
	auto* Comp_Burn = FindComponentByClass<UBurnComponent>();
	if (!IsValid(Comp_Burn))
	{
		return;
	}

	Comp_Burn->SetupBurnTargets(SKM_Windup);
	Comp_Burn->StartBurning();
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_Windup::Interact(AEHCharacter* Interacter)
{
	Super::Interact(Interacter);
	
	FInteractInfo Info = Component_Interact->GetSelectedInteractInfo();

	switch (CurrentInteractStep)
	{
	case EWindupInteractStep::NeedStopSound:
	{
		if (Info.InteractType == EInteractType::TurnOff)
		{
			StopWindup();

			CurrentInteractStep = EWindupInteractStep::NeedBurn;
			AllowNextInteract();
			Component_Interact->ShowInteracting(true);
		}

		else if (Info.InteractType == EInteractType::Burn)
		{
			StartWrongLoop();

			CurrentInteractStep = EWindupInteractStep::Finished;
		}
		break;
	}

	case EWindupInteractStep::NeedBurn:
	{
		if (Info.InteractType == EInteractType::Burn)
		{
			bSolved = true;
			CurrentInteractStep = EWindupInteractStep::Finished;
		}
		break;
	}
	}
}

#pragma endregion