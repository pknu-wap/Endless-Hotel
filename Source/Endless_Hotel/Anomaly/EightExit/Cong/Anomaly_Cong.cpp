// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Cong/Anomaly_Cong.h"
#include "Anomaly/Object/HandPrint/Anomaly_Object_HandPrint.h"
#include <Components/BoxComponent.h>

#pragma region Activity

void AAnomaly_Cong::ActivateAnomaly()
{
	Super::ActivateAnomaly();

	switch (AnomalyName)
	{
	case EAnomalyName::Cong:
		AnomalyAction = ([this](AAnomaly_Object_Base* Object)
			{
				StartCongCong();
			});
		ActiveTrigger();
		break;
	}
}

#pragma endregion

#pragma region Cong

void AAnomaly_Cong::StartCongCong()
{
	CongDelegate = FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			TArray<AActor*> RemoveTargets;

			for (auto* FoundActor : LinkedObjects)
			{
				auto* HandPrint = Cast<AAnomaly_Object_HandPrint>(FoundActor);

				if (CurrentIndex == HandPrint->HandPrintIndex)
				{
					HandPrint->StartCongCong(NextCong);
					RemoveTargets.Add(FoundActor);
				}
			}

			for (auto* RemoveTarget : RemoveTargets)
			{
				LinkedObjects.Remove(RemoveTarget);
			}

			if (CurrentIndex >= MaxIndex)
			{
				GetWorld()->GetTimerManager().ClearTimer(CongHandle);
				return;
			}

			CurrentIndex++;
			GetWorld()->GetTimerManager().SetTimer(CongHandle, CongDelegate, NextCong, false);
		});

	GetWorld()->GetTimerManager().SetTimer(CongHandle, CongDelegate, 0.01f, false);

	AAnomaly_Object_HandPrint::bIsFirstHandPrint = true;
}

#pragma endregion