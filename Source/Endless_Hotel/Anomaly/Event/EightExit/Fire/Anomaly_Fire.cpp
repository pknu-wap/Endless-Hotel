// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/Fire/Anomaly_Fire.h"
#include "Anomaly/Object/EightExit/Fire/Anomaly_Object_Candle.h"
#include "Player/Character/EHPlayer.h"
#include <Kismet/GameplayStatics.h>
#include <NiagaraFunctionLibrary.h>
#include <NiagaraComponent.h>
#include <Components/AudioComponent.h>

#pragma region Activity

void AAnomaly_Fire::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyID)
	{
	case EAnomalyID::Fire:
		SetupAnomalyAction<AAnomaly_Object_Candle>(&AAnomaly_Object_Candle::FallCandle);
		SetupAnomalyAction<ThisClass>(&ThisClass::StartFire);
		ActiveTrigger();
		break;
	}
}

void AAnomaly_Fire::DisableAnomaly()
{
	Super::DisableAnomaly();

	if (EHPlayer.IsValid())
	{
		EHPlayer->OnCrouched.RemoveAll(this);
	}

	GetWorld()->GetTimerManager().ClearTimer(FireHandle);
	GetWorld()->GetTimerManager().ClearTimer(SmokeHandle);
	GetWorld()->GetTimerManager().ClearTimer(JilsikHandle);

	for (auto Target : SpawnedFires)
	{
		Target->Destroy();
	}

	for (auto Target : SpawnedSmokes)
	{
		Target->DestroyComponent();
	}

	SpawnedSmokes.Empty();

	FireSpawnIndex = 0;
}

#pragma endregion

#pragma region Fire

void AAnomaly_Fire::StartFire()
{
	FTimerHandle SpawnHandle;
	GetWorld()->GetTimerManager().SetTimer(SpawnHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			SpawnFires();
			SpawnSmokes();
			SmokeTimer(false);
		}), 0.5f, false);
}

void AAnomaly_Fire::SpawnFires()
{
	EHPlayer = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	EHPlayer->OnCrouched.AddUObject(this, &ThisClass::SmokeTimer);

	constexpr float FireSpawnDuration = 1.0f;
	GetWorld()->GetTimerManager().SetTimer(FireHandle, this, &ThisClass::SpawnFire, FireSpawnDuration, true);
}

void AAnomaly_Fire::SpawnFire()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	UWorld* World = GetWorld();
	auto* SpawnedFire = World->SpawnActor<AActor>(FireClass, FireSpawnPositions[FireSpawnIndex++], FRotator::ZeroRotator, SpawnInfo);
	SpawnedFires.Add(SpawnedFire);

	if (!FireSpawnPositions.IsValidIndex(FireSpawnIndex))
	{
		World->GetTimerManager().ClearTimer(FireHandle);
	}
}

#pragma endregion

#pragma region Smoke

void AAnomaly_Fire::SmokeTimer(bool bIsCrouch)
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (bIsCrouch)
	{
		TimerManager.ClearTimer(JilsikHandle);
		return;
	}

	FTimerHandle CoughHandle;
	TimerManager.SetTimer(CoughHandle, this, &ThisClass::PlayCoughSound, 2.f, false);

	constexpr float JilsikDuration = 10.f;
	TimerManager.SetTimer(JilsikHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			PlayCoughSound();
			EHPlayer->OnDie.Broadcast(EDeathReason::Smoke);
		}), JilsikDuration, false);
}

void AAnomaly_Fire::SpawnSmokes()
{
	constexpr float SmokeSpawnDuration = 2.0f;
	GetWorld()->GetTimerManager().SetTimer(SmokeHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			auto* NS = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_Smoke, SmokeTransform[SmokeSpawnIndex].GetLocation(), SmokeTransform[SmokeSpawnIndex].Rotator());
			SpawnedSmokes.Add(NS);

			++SmokeSpawnIndex;

			if (!SmokeTransform.IsValidIndex(SmokeSpawnIndex))
			{
				GetWorld()->GetTimerManager().ClearTimer(SmokeHandle);
			}
		}), SmokeSpawnDuration, true);
}

#pragma endregion

#pragma region Sound

void AAnomaly_Fire::PlayCoughSound()
{
	if (!IsValid(AC))
	{
		AC = UGameplayStatics::CreateSound2D(GetWorld(), SW_Cough);
	}

	if (!AC->IsPlaying())
	{
		AC->Play();
	}
}

#pragma endregion