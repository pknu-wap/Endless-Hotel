// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Rug/Anomaly_Rug.h"
#include "Anomaly/Object/EightExit/Rug/Anomaly_Object_Rug.h"

#pragma region Base

AAnomaly_Rug::AAnomaly_Rug()
{
	PrimaryActorTick.bCanEverTick = false;
}

#pragma endregion

#pragma region Activity

void AAnomaly_Rug::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyName::Rug_Color:
		SetupAnomalyAction(&AAnomaly_Object_Rug::ChangeRugColor);
		ScheduleAnomaly();
		break;
	}

}

#pragma endregion