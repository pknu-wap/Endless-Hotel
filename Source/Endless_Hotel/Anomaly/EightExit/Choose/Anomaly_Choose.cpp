// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/EightExit/Choose/Anomaly_Choose.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>

#pragma region Base

AAnomaly_Choose::AAnomaly_Choose(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

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
				FVector TargetLocation = ChooseStartPos;

				ACharacter* PlayerChar = UGameplayStatics::GetPlayerCharacter(this, 0);

				if (PlayerChar)
				{
					PlayerChar->SetActorLocation(TargetLocation, false, nullptr, ETeleportType::TeleportPhysics);

					UEHGameInstance* GI = Cast<UEHGameInstance>(GetGameInstance());
					if (GI)
					{
						if (GI->GlobalSelectedKeyIndex == 2)
						{
							SetVerdictMode(EAnomalyVerdictMode::Normal);
						}
					}
					
				}
			});
		ScheduleAnomaly();
		break;
	}
}

#pragma region Position



#pragma endregion
