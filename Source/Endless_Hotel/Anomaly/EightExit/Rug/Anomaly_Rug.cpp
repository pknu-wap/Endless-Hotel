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
		AnomalyAction = ([](AAnomaly_Object_Base* AnomalyObject)
			{
				Cast<AAnomaly_Object_Rug>(AnomalyObject)->ChangeRugColor();
			});
		ScheduleAnomaly();
		break;
	}

}

#pragma endregion