// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Object/Fire/Anomaly_Object_Candle.h"

#pragma region Base

AAnomaly_Object_Candle::AAnomaly_Object_Candle(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Object->SetSimulatePhysics(false);
}

#pragma endregion

#pragma region Fall

void AAnomaly_Object_Candle::FallCandle()
{
	Object->SetSimulatePhysics(true);
	Object->AddImpulse(ImpulseDirection.GetSafeNormal() * ImpulseStrength);
}

#pragma endregion