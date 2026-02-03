// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/Choose/Anomaly_Choose.h"

#pragma region Base

AAnomaly_Choose::AAnomaly_Choose(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}
#pragma endregion

#pragma region Activity

void AAnomaly_Choose::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();

	switch (AnomalyName)
	{
	case EAnomalyName::Choose:
		AnomalyAction = ([this](AAnomaly_Object_Base* AnomalyObject)
			{

			});
		ActiveTrigger();
		break;
	}
}

#pragma endregion