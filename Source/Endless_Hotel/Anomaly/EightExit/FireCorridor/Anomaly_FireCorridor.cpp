// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/FireCorridor/Anomaly_FireCorridor.h"

#pragma region Base

AAnomaly_FireCorridor::AAnomaly_FireCorridor(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PlayerStartTransform.SetLocation(FVector(-950, 566, 2016));
}

#pragma endregion