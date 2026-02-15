// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Choose/Anomaly_Choose.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"

#pragma region Base

AAnomaly_Choose::AAnomaly_Choose(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PlayerStartTransform.SetLocation(FVector(-916.5, 570, - 504)); //테스트용 좌표, 원래 좌표: -1010, 560, -900
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
				UAnomalyProgressSubSystem* APSS = Cast<UAnomalyProgressSubSystem>(GetGameInstance());
				if (APSS)
				{
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