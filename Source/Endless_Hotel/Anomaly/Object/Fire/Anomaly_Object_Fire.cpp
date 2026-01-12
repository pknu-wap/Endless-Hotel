// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Fire/Anomaly_Object_Fire.h"
#include <Niagara/Public/NiagaraComponent.h>
#include <Components/AudioComponent.h>

bool AAnomaly_Object_Fire::bIsFirst = true;

#pragma region Base

AAnomaly_Object_Fire::AAnomaly_Object_Fire(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(RootComponent);
	NiagaraComponent->SetAutoActivate(false);
	NiagaraComponent->Deactivate();

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(NiagaraComponent);
	AudioComponent->SetAutoActivate(false);
}

#pragma endregion

#pragma region Fire

void AAnomaly_Object_Fire::StartFire(UNiagaraSystem* Effect)
{
	NiagaraComponent->SetAsset(Effect);
	NiagaraComponent->Activate();

	if (bIsFirst)
	{
		AudioComponent->SetSound(SW_First);
		bIsFirst = false;
	}

	AudioComponent->Play();
}

#pragma endregion