// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Neapolitan/Float/Anomaly_Float.h"
#include "Anomaly/Object/Float/Anomaly_Object_Float.h"
#include "Component/Anomaly_Component_Restore.h"
#include <EngineUtils.h>
#include "Component/Anomaly_Float/Anomaly_Component_Float.h"

#pragma region Activity

void AAnomaly_Float::SetAnomalyActivate()
{
	Super::SetAnomalyActivate();

	switch (AnomalyName)
	{
	case EAnomalyName::Float:
		AnomalyAction = ([this](AAnomaly_Object_Base* Unused)
			{
                for (TActorIterator<AActor> It(GetWorld()); It; ++It)
                {
                    AActor* Target = *It;
                    auto* FloatComp = Target->FindComponentByClass<UAnomaly_Component_Float>();
                    auto* RestoreComp = Target->FindComponentByClass<UAnomaly_Component_Restore>();

                    if (FloatComp && RestoreComp)
                    {
                        FloatComp->StartFloating();

                        if (auto* BaseObj = Cast<AAnomaly_Object_Base>(Target))
                        {
                            BaseObj->InteractAction = [FloatComp, RestoreComp]()
                                {
                                    FloatComp->StopFloating();
                                    RestoreComp->StartRestoring(2.5f);
                                };
                        }
                    }
                }
			});
		ScheduleAnomaly(10);
		break;
	}
}

#pragma endregion