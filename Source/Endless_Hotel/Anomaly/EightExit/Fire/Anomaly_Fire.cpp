// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Fire/Anomaly_Fire.h"
#include "Anomaly/Object/EightExit/Fire/Anomaly_Object_Candle.h"
#include "Anomaly/Object/EightExit/Fire/Anomaly_Object_Fire.h"
#include "Player/Character/EHPlayer.h"
#include <Kismet/GameplayStatics.h>

#pragma region Activity

void AAnomaly_Fire::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyID::Fire:
		AnomalyActions.Add([this](AAnomaly_Object_Base* Candle)
			{
				Cast<AAnomaly_Object_Candle>(Candle)->FallCandle();

				GetWorld()->GetTimerManager().SetTimer(FireHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
					{
						SpawnFires();
					}), FireDuration, false);

				GetWorld()->GetTimerManager().SetTimer(SmokeHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
					{
						SmokeTimer(false);
					}), FireDuration, false);
			});
		ActiveTrigger();
		break;
	}
}

void AAnomaly_Fire::DisableAnomaly()
{
	Super::DisableAnomaly();

	if (IsValid(EHPlayer.Get()))
	{
		EHPlayer->CrouchDelegate.RemoveDynamic(this, &ThisClass::SmokeTimer);
	}

	GetWorld()->GetTimerManager().ClearTimer(FireHandle);
	GetWorld()->GetTimerManager().ClearTimer(SmokeHandle);

	for (auto Target : SpawnedFires)
	{
		Target->Destroy();
	}

	SpawnedFires.Empty();
}

#pragma endregion

#pragma region Fire

void AAnomaly_Fire::SpawnFires()
{
	EHPlayer = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	EHPlayer->CrouchDelegate.RemoveAll(this);
	EHPlayer->CrouchDelegate.AddDynamic(this, &ThisClass::SmokeTimer);

	GetWorld()->GetTimerManager().SetTimer(FireHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			int32 RandomIndex = FMath::RandRange(0, NS_Fires.Num() - 1);

			auto* SpawnedFire = GetWorld()->SpawnActor<AAnomaly_Object_Fire>(FireClass, FireSpawnPositions[CurrentSpawnIndex++], FRotator::ZeroRotator);
			SpawnedFire->StartFire(NS_Fires[RandomIndex]);

			SpawnedFires.Add(SpawnedFire);

			if (!FireSpawnPositions.IsValidIndex(CurrentSpawnIndex))
			{
				GetWorld()->GetTimerManager().ClearTimer(FireHandle);
			}
		}), FireSpawnDuration, true);
}

#pragma endregion

#pragma region Smoke

void AAnomaly_Fire::SmokeTimer(bool bIsCrouch)
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	FTimerManager& TimerManager = World->GetTimerManager();

	if (bIsCrouch)
	{
		TimerManager.ClearTimer(SmokeHandle);
		return;
	}

	TimerManager.SetTimer(SmokeHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			EHPlayer->DieDelegate.Broadcast(EDeathReason::Smoke);
		}), JilsikDuration, false);
}

#pragma endregion