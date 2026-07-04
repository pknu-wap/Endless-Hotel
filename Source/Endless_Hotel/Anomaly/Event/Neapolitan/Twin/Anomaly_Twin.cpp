// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Event/Neapolitan/Twin/Anomaly_Twin.h"
#include "Character/AI/Twin/Twin.h"
#include "Player/Character/EHPlayer.h"
#include <Components/BoxComponent.h>

#pragma region Twin

void AAnomaly_Twin::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyID::Twin:
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

void AAnomaly_Twin::OnTriggerBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEHPlayer* Player = Cast<AEHPlayer>(OtherActor);
	if (!Player)
	{
		return;
	}
	StartTwin();
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

#pragma endregion