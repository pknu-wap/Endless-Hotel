// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Bug/Anomaly_Object_Bug.h"
#include <Niagara/Public/NiagaraComponent.h>
#include <Components/AudioComponent.h>

#pragma region Base

AAnomaly_Object_Bug::AAnomaly_Object_Bug(const FObjectInitializer& ObjectInitializer)
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

#pragma region Bug

void AAnomaly_Object_Bug::ActiveBug()
{
	NiagaraComponent->Activate();
	AudioComponent->Play();
}

#pragma endregion