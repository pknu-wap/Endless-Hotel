// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Fire/Anomaly_Fire.h"
#include "Anomaly/Object/Fire/Anomaly_Object_Candle.h"
#include "Anomaly/Object/Fire/Anomaly_Object_Fire.h"

#pragma region Activity

void AAnomaly_Fire::ActivateAnomaly()
{
	Super::ActivateAnomaly();

	switch (AnomalyID)
	{
	case 14:
		AnomalyAction = ([this](AAnomaly_Object_Base* Candle)
			{
				Cast<AAnomaly_Object_Candle>(Candle)->FallCandle();

				FTimerHandle FireHandle;
				GetWorld()->GetTimerManager().SetTimer(FireHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
					{
						SpawnFires();
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