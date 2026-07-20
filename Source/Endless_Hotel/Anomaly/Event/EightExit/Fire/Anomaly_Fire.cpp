// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/Fire/Anomaly_Fire.h"
#include "Anomaly/Object/EightExit/Fire/Anomaly_Object_Candle.h"
#include "Anomaly/Object/EightExit/Fire/Anomaly_Object_Fire.h"
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
		EHPlayer->CrouchDelegate.RemoveDynamic(this, &ThisClass::SmokeTimer);
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

	SpawnedFires.Empty();
	SpawnedSmokes.Empty();
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
	EHPlayer->CrouchDelegate.AddUniqueDynamic(this, &ThisClass::SmokeTimer);

	constexpr float FireSpawnDuration = 1.0f;
	GetWorld()->GetTimerManager().SetTimer(FireHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			auto* SpawnedFire = GetWorld()->SpawnActor<AAnomaly_Object_Fire>(FireClass, FireSpawnPositions[FireSpawnIndex++], FRotator::ZeroRotator);
			SpawnedFire->StartFire(NS_Fire);

			SpawnedFires.Add(SpawnedFire);

			if (!FireSpawnPositions.IsValidIndex(FireSpawnIndex))
			{
				GetWorld()->GetTimerManager().ClearTimer(FireHandle);
			}
		}), FireSpawnDuration, true);
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
			EHPlayer->DieDelegate.Broadcast(EDeathReason::Smoke);
		}), JilsikDuration, false);
}

void AAnomaly_Fire::SpawnSmokes()
{
	constexpr float FireSpawnDuration = 5.0f;
	GetWorld()->GetTimerManager().SetTimer(SmokeHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			auto* NS = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_Smoke, SmokeTransform[SmokeSpawnIndex].GetLocation(), SmokeTransform[SmokeSpawnIndex].Rotator());
			SpawnedSmokes.Add(NS);

			++SmokeSpawnIndex;

			if (!SmokeTransform.IsValidIndex(SmokeSpawnIndex))
			{
				GetWorld()->GetTimerManager().ClearTimer(SmokeHandle);
			}
		}), FireSpawnDuration, true);
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