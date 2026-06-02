// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/EightExit/Bug/Anomaly_Object_Bug.h"
#include <Niagara/Public/NiagaraComponent.h>
#include <Components/AudioComponent.h>

#pragma region Base

AAnomaly_Object_Bug::AAnomaly_Object_Bug(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(RootComponent);
	SetNiagaraComponent();

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->SetAutoActivate(false);
}

#pragma endregion

#pragma region Reset

void AAnomaly_Object_Bug::Reset()
{
	Super::Reset();

	auto* Asset = NiagaraComponent->GetAsset();
	NiagaraComponent->DeactivateImmediate();
	NiagaraComponent->DestroyComponent();
	NiagaraComponent = NewObject<UNiagaraComponent>();
	NiagaraComponent->SetAsset(Asset);
	NiagaraComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SetNiagaraComponent();

	AudioComponent->Stop();
	
	Destroy();
}

#pragma endregion

#pragma region Bug

void AAnomaly_Object_Bug::ActiveBug()
{
	NiagaraComponent->Activate();
	AudioComponent->Play();
}

void AAnomaly_Object_Bug::SetNiagaraComponent()
{
	NiagaraComponent->SetAutoActivate(false);
	NiagaraComponent->Deactivate();
}

#pragma endregion