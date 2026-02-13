// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Cong/Anomaly_Cong.h"
#include "Anomaly/Object/HandPrint/Anomaly_Object_HandPrint.h"
#include <Components/BoxComponent.h>

#pragma region Activity

void AAnomaly_Cong::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();

	switch (AnomalyName)
	{
	case EAnomalyName::Cong:
		AnomalyAction = ([this](AAnomaly_Object_Base* AnomalyObject)
			{
				Cast<AAnomaly_Object_HandPrint>(AnomalyObject)->ReserveCongCong();
			});
		ActiveTrigger();
		break;
	}
}

#pragma endregion