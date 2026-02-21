// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/FootStep/Anomaly_FootStep.h"
#include "Anomaly/Object/EightExit/FootStep/Anomaly_Object_FootStep.h"


void AAnomaly_FootStep::SetAnomalyActivate()
{
    Super::SetAnomalyActivate();

    switch (AnomalyName) {
    case EAnomalyName::FootStep:
        AnomalyAction = ([this](AAnomaly_Object_Base* Object)
            {
                Cast<AAnomaly_Object_FootStep>(Object)->ChangeFootStep();
            });
        ScheduleAnomaly(10);
        break;
    }
}
