// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Object/Neapolitan/Wind-up/Anomaly_Object_Windup.h"
#include "Component/Interact/InteractComponent.h"
#include <Components/AudioComponent.h>

#pragma region Base

AAnomaly_Object_Windup::AAnomaly_Object_Windup(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SKM_Windup = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SKM_Windup"));
	SKM_Windup->SetupAttachment(RootComponent);

	AC_Windup = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_Windup"));
	AC_Windup->SetupAttachment(RootComponent);
}

void AAnomaly_Object_Windup::BeginPlay()
{
	Super::BeginPlay();

	AC_Windup->SetSound(Sound_Windup);
	SKM_Windup->SetHiddenInGame(false);
	Object->SetHiddenInGame(false);
}

#pragma endregion

#pragma region Sound

void AAnomaly_Object_Windup::StartWindupLoop()
{
	CurrentWindupPlayCount = 0;

	WindupLoopTick();

	GetWorld()->GetTimerManager().SetTimer(WindupPlayHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			WindupLoopTick();
		}), WindupPlayInterval, true);
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
	AC_Windup->Play();
	PlayWindupAnimationOnce();
}

void AAnomaly_Object_Windup::StopWindup()
{
	GetWorld()->GetTimerManager().ClearTimer(WindupPlayHandle);
	AC_Windup->Stop();
}

void AAnomaly_Object_Windup::StartWrongLoop()
{
	GetWorld()->GetTimerManager().ClearTimer(WindupPlayHandle);
	AC_Windup->Stop();

	CurrentWrongPlayCount = 0;

	WrongLoopTick();

	GetWorld()->GetTimerManager().SetTimer(WrongPlayHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			WrongLoopTick();
		}), WrongPlayInterval, true);
}

void AAnomaly_Object_Windup::WrongLoopTick()
{
	if (CurrentWrongPlayCount >= WrongPlayCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(WrongPlayHandle);
		
		SetupBurnTargets();
		StartBurning(BurnDuration);

		return;
	}
	
	WindupPlay();
	CurrentWrongPlayCount++;
}

#pragma endregion

#pragma region Animation
void AAnomaly_Object_Windup::PlayWindupAnimationOnce()
{
	SKM_Windup->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	SKM_Windup->SetAnimation(WindupAnimation);
	SKM_Windup->SetPosition(0.0f, false);
	SKM_Windup->Play(false);
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
				SetupBurnTargets();
				StartBurning(BurnDuration);

				bSolved = true;
				CurrentInteractStep = EWindupInteractStep::Finished;
			}
			break;
		}
	}
}

#pragma endregion