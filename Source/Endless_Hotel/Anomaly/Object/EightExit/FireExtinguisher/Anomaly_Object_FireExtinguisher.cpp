// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Object/EightExit/FireExtinguisher/Anomaly_Object_FireExtinguisher.h"
#include <Niagara/Public/NiagaraComponent.h>
#include <Components/AudioComponent.h>

#pragma region Base

AAnomaly_Object_FireExtinguisher::AAnomaly_Object_FireExtinguisher(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->SetAutoActivate(false);

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(RootComponent);
	NiagaraComponent->Deactivate();
	NiagaraComponent->SetAutoActivate(false);
}

#pragma endregion

#pragma region Explode

void AAnomaly_Object_FireExtinguisher::Explode()
{
	Object->SetVisibility(false);
	AudioComponent->Play();
	NiagaraComponent->Activate();
	FTimerHandle DeactiveHandle;
	GetWorld()->GetTimerManager().SetTimer(DeactiveHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			NiagaraComponent->Deactivate();
		}), 4.5f, false);
}

#pragma endregion