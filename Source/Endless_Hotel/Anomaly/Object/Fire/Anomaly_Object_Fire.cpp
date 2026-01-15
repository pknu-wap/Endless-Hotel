// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Fire/Anomaly_Object_Fire.h"
#include "Player/Character/EHPlayer.h"
#include <Niagara/Public/NiagaraComponent.h>
#include <Components/AudioComponent.h>
#include <Components/BoxComponent.h>

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

	DeathTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("DeathTrigger"));
	DeathTrigger->SetupAttachment(NiagaraComponent);
	DeathTrigger->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnDeathRange);
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

	DeathTrigger->SetWorldLocation(NiagaraComponent->GetComponentLocation());
}

#pragma endregion

#pragma region Death

void AAnomaly_Object_Fire::OnDeathRange(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEHPlayer* Player = Cast<AEHPlayer>(OtherActor);

	if (!Player)
	{
		return;
	}

	Player->DieDelegate.Broadcast(EDeathReason::Burn);
}

#pragma endregion