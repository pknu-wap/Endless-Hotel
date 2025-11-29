// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Cong/Anomaly_Cong.h"
#include "Anomaly/Object/HandPrint/Anomaly_Object_HandPrint.h"

#pragma region Activity

void AAnomaly_Cong::ActivateAnomaly(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly(Anomaly_ID);

	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			StartAnomalyAction();
		}), 15, false);
}

#pragma endregion

#pragma region Cong

void AAnomaly_Cong::StartAnomalyAction()
{
	CongDelegate = FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			for (auto* FoundActor : LinkedObjects)
			{
				auto* HandPrint = Cast<AAnomaly_Object_HandPrint>(FoundActor);

				if (CurrentIndex == HandPrint->HandPrintIndex)
				{
					HandPrint->StartCongCong(NextCong);
				}
			}

			if (CurrentIndex >= MaxIndex)
			{
				GetWorld()->GetTimerManager().ClearTimer(CongHandle);
				return;
			}

			CurrentIndex++;
			GetWorld()->GetTimerManager().SetTimer(CongHandle, CongDelegate, NextCong, false);
		});

	GetWorld()->GetTimerManager().SetTimer(CongHandle, CongDelegate, NextCong, false);

	AAnomaly_Object_HandPrint::bIsFirstHandPrint = true;
}

#pragma endregion