// Copyright by 2026-1 WAP Game 2 team


#include "Anomaly/Object/Neapolitan/Wind-up/Anomaly_Object_Windup.h"
#include "Component/Interact/InteractComponent.h"
#include <Components/AudioComponent.h>

#pragma region Base

AAnomaly_Object_Windup::AAnomaly_Object_Windup(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AC_Windup = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_Windup"));
	AC_Windup->SetupAttachment(RootComponent);

	AC_Wrong = CreateDefaultSubobject<UAudioComponent>(TEXT("AC_Wrong"));
	AC_Wrong->SetupAttachment(RootComponent);
}

void AAnomaly_Object_Windup::BeginPlay()
{
	Super::BeginPlay();

	AC_Windup->SetSound(Sound_Windup);
	WindupPlay();

	AC_Wrong->SetSound(Sound_Wrong);
}

#pragma endregion

#pragma region Sound

void AAnomaly_Object_Windup::WindupPlay()
{
	AC_Windup->Play();
}

void AAnomaly_Object_Windup::StopWindup()
{
	AC_Windup->Stop();
}

void AAnomaly_Object_Windup::WrongPlay()
{
	AC_Wrong->Play();
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
			}

			else if(Info.InteractType == EInteractType::Burn)
			{
				SetupBurnTargets();
				StartBurning(BurnDuration);

				WrongPlay();

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

				CurrentInteractStep = EWindupInteractStep::Finished;
			}
			break;
		}
		
		case EWindupInteractStep::Finished:
			break;
	}
}

#pragma endregion