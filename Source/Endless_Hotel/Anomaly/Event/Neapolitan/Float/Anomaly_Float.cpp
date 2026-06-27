// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/Neapolitan/Float/Anomaly_Float.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include <Kismet/GameplayStatics.h>
#include <Components/AudioComponent.h>

#pragma region Activity

void AAnomaly_Float::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyID::Float:
		SetupAnomalyAction(&AAnomaly_Object_Base::StartFloating, { EInteractType::Restore });
		ScheduleAnomaly(10);
		break;
	}
}

void AAnomaly_Float::StartAnomalyAction()
{
	Super::StartAnomalyAction();

	PlayGravitySound();
}

#pragma endregion

#pragma region Sound

void AAnomaly_Float::PlayGravitySound()
{
	auto* AC = UGameplayStatics::CreateSound2D(GetWorld(), SW_Gravity);
	AC->Play();
}

#pragma endregion