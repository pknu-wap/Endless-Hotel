// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Ghost/Anomaly_Ghost.h"
#include "Anomaly/Object/Ghost/Anomaly_Object_Ghost.h"

void AAnomaly_Ghost::SetAnomalyActivate()
{
    Super::SetAnomalyActivate();

    switch (AnomalyID)
    {
    case 28:
        AnomalyAction = [](AAnomaly_Object_Base* Obj)
            {
                Cast<AAnomaly_Object_Ghost>(Obj)->bTriggerEnabled = true;
            };
        break;
    }
    StartAnomalyAction();
}