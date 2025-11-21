// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/EightExit/Cong/Anomaly_Cong.h"
#include "Anomaly/Object/HandPrint/Anomaly_Object_HandPrint.h"

#pragma region Activity

void AAnomaly_Cong::ActivateAnomaly_Implementation(uint8 Anomaly_ID)
{
	Super::ActivateAnomaly_Implementation(Anomaly_ID);

	StartCongAction();
}

#pragma endregion

#pragma region Cong

void AAnomaly_Cong::StartCongAction()
{
	const uint8 MaxIndex = 100;
	uint8 CurrentIndex = 0;

	TWeakObjectPtr<AAnomaly_Cong> Wrapper = this;
	GetWorld()->GetTimerManager().SetTimer(CongHandle, [Wrapper, MaxIndex, CurrentIndex]() mutable
		{
			for (auto* FoundActor : Wrapper->LinkedObjects)
			{
				auto* HandPrint = Cast<AAnomaly_Object_HandPrint>(FoundActor);

				if (++CurrentIndex == HandPrint->HandPrintIndex)
				{
					HandPrint->StartCongCong(Wrapper->NextCong);
				}

				if (CurrentIndex >= MaxIndex)
				{
					Wrapper->GetWorld()->GetTimerManager().ClearTimer(Wrapper->CongHandle);
				}
			}
		}, NextCong, true);
}

#pragma endregion