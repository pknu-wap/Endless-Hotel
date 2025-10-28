// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Light/Anomaly_Light.h"
#include "Anomaly/Object/Light/Anomaly_Object_Light.h"
#include "Kismet/GameplayStatics.h"

#pragma region Base

// For test
void AAnomaly_Light::BeginPlay()
{
	Super::BeginPlay();

	ActivateAnomaly_Implementation();
}

#pragma endregion

#pragma region Activity

void AAnomaly_Light::ActivateAnomaly_Implementation()
{
	Super::ActivateAnomaly_Implementation();

	// 이 부분은 ID를 넘겨받는 부분이 생기면 바로 수정 예정
	/*switch (Anomaly_ID)
	{
		case ?:
			LightAction = ([](AAnomaly_Object_Light* Light) {Light->ChangeLightColor(); });
		break;

		case ?:
			LightAction = ([](AAnomaly_Object_Light* Light) {Light->DropLight(); });
			break;
	}*/

	StartLightAction();
}

#pragma endregion

#pragma region Light

void AAnomaly_Light::StartLightAction()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAnomaly_Object_Light::StaticClass(), OUT FoundActors);

	FTimerHandle LightHandle;
	GetWorld()->GetTimerManager().SetTimer(LightHandle, [this, LightHandle, FoundActors]() mutable
		{
			for (auto* FoundActor : FoundActors)
			{
				auto* Light = Cast<AAnomaly_Object_Light>(FoundActor);
				if (CurrentIndex == Light->LightIndex)
				{
					LightAction(Light);
				}
			}

			if (++CurrentIndex > MaxIndex)
			{
				GetWorld()->GetTimerManager().ClearTimer(LightHandle);
			}
		}, 0.5f, true);
}

#pragma endregion