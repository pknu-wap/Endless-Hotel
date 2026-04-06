// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Cong/Anomaly_Cong.h"
#include "Anomaly/Object/EightExit/HandPrint/Anomaly_Object_HandPrint.h"
#include <Components/BoxComponent.h>

#pragma region Activity

void AAnomaly_Cong::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyName::Cong:
		SetupAnomalyAction(&AAnomaly_Object_HandPrint::ReserveCongCong);
		ActiveTrigger();
		break;
	}
}

void AAnomaly_Cong::DisableAnomaly()
{
	Super::DisableAnomaly();

	AAnomaly_Object_HandPrint::bIsFirstHandPrint = true;
}

#pragma endregion