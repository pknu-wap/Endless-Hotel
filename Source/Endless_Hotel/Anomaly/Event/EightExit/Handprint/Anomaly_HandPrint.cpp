// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/HandPrint/Anomaly_HandPrint.h"
#include "Anomaly/Object/EightExit/HandPrint/Anomaly_Object_HandPrint.h"
#include "Anomaly/Object/EightExit/Light/Anomaly_Object_Light.h"

#pragma region Activity

void AAnomaly_HandPrint::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyID::Handprint:
		ActiveTrigger();
		break;
	}
}

void AAnomaly_HandPrint::DisableAnomaly()
{
	for (AAnomaly_Object_HandPrint* HandPrint : SpawnedHandPrint)
	{
		HandPrint->Destroy();
	}

	SpawnedHandPrint.Empty();

	TurnAllLights(true);

	Super::DisableAnomaly();
}

void AAnomaly_HandPrint::StartAnomalyAction()
{
	SpawnHandPrint();
	TurnAllLights(false);
}

#pragma endregion

#pragma region HandPrint

void AAnomaly_HandPrint::SpawnHandPrint()
{
	UWorld* World = GetWorld();

	uint8 Index = 0;
	for (auto Trans : HandPrintTrans)
	{
		auto* HandPrint = World->SpawnActor<AAnomaly_Object_HandPrint>(HandPrintClass, Trans);
		HandPrint->ShowHandPrint(++Index);
		SpawnedHandPrint.Add(HandPrint);
	}
}

#pragma endregion

#pragma region Light

void AAnomaly_HandPrint::TurnAllLights(bool bOn)
{
	for (AAnomaly_Object_Base* Target : TargetAnomalyObjects)
	{
		auto* Light = Cast<AAnomaly_Object_Light>(Target);
		Light->TurnLight(bOn);
	}
}

#pragma endregion