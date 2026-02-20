// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Ghost/Anomaly_Ghost.h"
#include "Anomaly/Object/Neapolitan/Ghost/Anomaly_Object_Ghost.h"

void AAnomaly_Ghost::SetAnomalyActivate()
{
    Super::SetAnomalyActivate();

    switch (AnomalyName)
    {
    case EAnomalyName::Ghost:
        AnomalyAction = ([this](AAnomaly_Object_Base* Obj)
            {
                   Cast<AAnomaly_Object_Ghost>(Obj)->bTriggerEnabled = true;
            });
        ScheduleAnomaly();
        break;
    }
}