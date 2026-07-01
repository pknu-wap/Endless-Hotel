// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/EightExit/Fire/Anomaly_Object_Candle.h"

#pragma region Reset

void AAnomaly_Object_Candle::Reset()
{
	Object->SetSimulatePhysics(false);
	Object->SetEnableGravity(false);

	Super::Reset();
}

#pragma endregion

#pragma region Fall

void AAnomaly_Object_Candle::FallCandle()
{
	Object->SetSimulatePhysics(true);
	Object->SetEnableGravity(true);
	Object->AddImpulse(ImpulseDirection.GetSafeNormal() * ImpulseStrength);
}

#pragma endregion