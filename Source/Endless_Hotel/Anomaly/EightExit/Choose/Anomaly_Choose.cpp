// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Choose/Anomaly_Choose.h"
#include "GameSystem/SubSystem/GameSystem.h"

#pragma region Base

AAnomaly_Choose::AAnomaly_Choose(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	PlayerStartTransform.SetLocation(FVector(-740.0, 570, - 650));
	PlayerStartTransform.SetRotation(FRotator(0.f, -90.f, 0.f).Quaternion()); //테스트용 좌표, 원래 좌표: -1010, 560, -900

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