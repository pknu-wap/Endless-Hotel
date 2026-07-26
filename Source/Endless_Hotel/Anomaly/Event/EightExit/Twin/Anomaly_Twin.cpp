// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/Twin/Anomaly_Twin.h"
#include "Character/AI/Twin/Twin.h"
#include "Player/Character/EHPlayer.h"
#include <Components/BoxComponent.h>

#pragma region Twin

void AAnomaly_Twin::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyID)
	{
	case EAnomalyID::Twin:
		SetupAnomalyAction<AAnomaly_Twin>(&AAnomaly_Twin::StartTwin);
		break;
	}
	ActiveTrigger();
}

void AAnomaly_Twin::DisableAnomaly()
{
	for (const auto& Twin : Twins)
	{
		ATwin* StrongTwin = Twin.Get();
		StrongTwin->Destroy();
	}
	Super::DisableAnomaly();
}

void AAnomaly_Twin::StartTwin()
{
	for (const auto& Transform : Transforms)
	{
		Twins.Add(GetWorld()->SpawnActor<ATwin>(TwinClass, Transform));
	}
}

#pragma endregion