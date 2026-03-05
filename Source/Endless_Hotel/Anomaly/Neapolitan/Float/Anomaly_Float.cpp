// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Neapolitan/Float/Anomaly_Float.h"
#include "Anomaly/Object/Neapolitan/Float/Anomaly_Object_Float.h"
#include "Component/Float/FloatComponent.h"
#include <Kismet/GameplayStatics.h>

#pragma region Activity

void AAnomaly_Float::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyName::Float:
		AnomalyAction = ([this](AAnomaly_Object_Base* Float)
			{
                for (auto* Obj : LinkedObjects)
                {
                    UFloatComponent* FloatComp = Obj->FindComponentByClass<UFloatComponent>();
                    if (FloatComp)
                    {
                        FloatComp->StartFloating();
                    }
                }
			});
		ScheduleAnomaly(10);
		break;
	}
}

#pragma endregion


