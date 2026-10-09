// Copyright by 2026-1 WAP Game 2 team

#include "Anomaly/Event/Neapolitan/Eye/Anomaly_Eye.h"
#include "Anomaly/Object/Neapolitan/Eye/Anomaly_Object_Eye.h"
#include "Player/Camera/EHPlayerCameraManager.h"
#include <Kismet/GameplayStatics.h>

#pragma region Activity

void AAnomaly_Eye::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyID)
	{
	case EAnomalyID::Eye:
		SetupAnomalyAction<AAnomaly_Object_Eye>(&AAnomaly_Object_Eye::StartEyeAppear);
		SetupAnomalyAction<ThisClass>(&ThisClass::StartEyeFocus);
		ActiveTrigger();
		break;
	}
}

#pragma endregion

#pragma region EyeFocus
	
void AAnomaly_Eye::StartEyeFocus()
{
	const auto& PlayerCameraManager = Cast<AEHPlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0));
	PlayerCameraManager->StartHallucination(true);
}

#pragma endregion