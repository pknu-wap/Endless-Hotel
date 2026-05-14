// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Choose/Anomaly_Choose.h"
#include "GameSystem/SubSystem/GameSystem.h"

#pragma region Activity

void AAnomaly_Choose::SetAnomalyState()
{
	Super::SetAnomalyState();

	switch (AnomalyName)
	{
	case EAnomalyID::Choose:
		AnomalyActions.Add([this](AAnomaly_Object_Base* AnomalyObject)
			{
				if (UGameInstance* GI = GetGameInstance())
				{
					UGameSystem* APSS = GI->GetSubsystem<UGameSystem>();

					if (APSS->GlobalSelectedKeyIndex == 2)
					{
						SetVerdictMode(EAnomalyVerdictMode::Normal);
					}
				}
			});
		ScheduleAnomaly();
		break;
	}
}

#pragma endregion