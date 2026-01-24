// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Fire/Anomaly_Fire.h"
#include "Anomaly/Object/Fire/Anomaly_Object_Candle.h"
#include "Anomaly/Object/Fire/Anomaly_Object_Fire.h"
#include "Player/Character/EHPlayer.h"
#include <Kismet/GameplayStatics.h>

#pragma region Base

void AAnomaly_Fire::BeginPlay()
{
	Super::BeginPlay();

	EHPlayer = Cast<AEHPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	EHPlayer->CrouchDelegate.AddDynamic(this, &ThisClass::SmokeTimer);
}

#pragma endregion

#pragma region Activity

void AAnomaly_Fire::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();

	switch (AnomalyName)
	{
	case EAnomalyName::Fire:
		AnomalyAction = ([this](AAnomaly_Object_Base* Candle)
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

#pragma endregion

#pragma region Fire

void AAnomaly_Fire::SpawnFires()
{
	GetWorld()->GetTimerManager().SetTimer(FireHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			int32 RandomIndex = FMath::RandRange(0, NS_Fires.Num() - 1);

			auto* SpawnedFire = GetWorld()->SpawnActor<AAnomaly_Object_Fire>(FireClass, FireSpawnPositions[CurrentSpawnIndex++], FRotator::ZeroRotator);
			SpawnedFire->StartFire(NS_Fires[RandomIndex]);

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
	if (bIsCrouch)
	{
		GetWorld()->GetTimerManager().ClearTimer(SmokeHandle);
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(SmokeHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			EHPlayer->DieDelegate.Broadcast(EDeathReason::Smoke);
		}), 5, false);
}

#pragma endregion