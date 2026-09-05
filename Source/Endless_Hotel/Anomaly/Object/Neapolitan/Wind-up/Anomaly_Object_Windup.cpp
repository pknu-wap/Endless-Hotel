// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Wind-up/Anomaly_Object_Windup.h"
#include "Component/Interact/InteractComponent.h"
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

void AAnomaly_Object_Windup::Reset()
{
	Super::Reset();

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
	StartWindupBurning();
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

	AnimInstance->PlaySlotAnimationAsDynamicMontage(WrongWindupAnimation, TEXT("DefaultSlot"), 0.f, 0.f, 1.f,	WrongPlayCount);
}
#pragma endregion

#pragma region Burn

void AAnomaly_Object_Windup::SetupWindupBurnTargets()
{
	for (int32 Index = 0; Index < SKM_Windup->GetNumMaterials(); ++Index)
	{
		auto* Material = SKM_Windup->CreateDynamicMaterialInstance(Index);
		Material->SetScalarParameterValue(TEXT("Alpha"), 0.f);
		Material->SetVectorParameterValue(TEXT("Edge Color"), EdgeColor * ColorBoost);
		Material->SetTextureParameterValue(TEXT("Dissolve Texture"), DissolveTexture);

		MID_WindupBurn.Add(Material);

		SKM_Windup->SetMaterial(Index, MID_WindupBurn[Index]);
	}
}

void AAnomaly_Object_Windup::StartWindupBurning()
{
	SetupWindupBurnTargets();
	Niagara_Fire->Activate();
	AC->Play();
	GetWorld()->GetTimerManager().SetTimer(WindupBurnHandle, this, &ThisClass::WindupBurnTick,0.02f, true);
}

void AAnomaly_Object_Windup::WindupBurnTick()
{
	WindupBurnCurrentTime += 0.02f;
	constexpr float BurnDuration = 5.f;
	const float Alpha =	FMath::Clamp(WindupBurnCurrentTime / BurnDuration, 0.f, 1.f);

	for (int32 Index = 0; Index < MID_WindupBurn.Num(); ++Index)
	{
		MID_WindupBurn[Index]->SetScalarParameterValue(TEXT("Alpha"), Alpha);
	}

	if (Alpha >= 1.f)
	{
		SKM_Windup->SetHiddenInGame(true);
		Object->SetHiddenInGame(true);
		Niagara_Fire->Deactivate();

		GetWorld()->GetTimerManager().ClearTimer(WindupBurnHandle);
		SKM_Windup->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

#pragma endregion

#pragma region Interact

void AAnomaly_Object_Windup::Interact_Implementation(AEHCharacter* Interacter)
{
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

			else if(Info.InteractType == EInteractType::Burn)
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
				StartWindupBurning();

				bSolved = true;
				CurrentInteractStep = EWindupInteractStep::Finished;
			}
			break;
		}
	}
}

#pragma endregion