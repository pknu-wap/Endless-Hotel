// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/FootStep/Anomaly_FootStep.h"
#include "Anomaly/Object/EightExit/FootStep/Anomaly_Object_FootStep.h"


void AAnomaly_FootStep::SetAnomalyState()
{
    Super::SetAnomalyState();

    switch (AnomalyName) {
    case EAnomalyName::FootStep:
        AnomalyAction = MakeAnomalyAction(&AAnomaly_Object_FootStep::ChangeFootStep);
        ScheduleAnomaly(10);
        break;
    }
}
