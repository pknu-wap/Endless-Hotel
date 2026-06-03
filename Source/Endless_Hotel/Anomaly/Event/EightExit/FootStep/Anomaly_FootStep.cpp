// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Event/EightExit/FootStep/Anomaly_FootStep.h"
#include "Anomaly/Object/EightExit/FootStep/Anomaly_Object_FootStep.h"

#pragma region Activity

void AAnomaly_FootStep::SetAnomalyState()
{
    Super::SetAnomalyState();

    switch (AnomalyName) {
    case EAnomalyID::FootStep:
        SetupAnomalyAction(&AAnomaly_Object_FootStep::StartFootStep);
        ScheduleAnomaly(20);
        break;
    }
}

#pragma endregion