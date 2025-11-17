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

	GetWorld()->GetTimerManager().SetTimer(CongHandle, [this, MaxIndex, CurrentIndex]() mutable
		{
			for (auto* FoundActor : LinkedObjects)
			{
				auto* HandPrint = Cast<AAnomaly_Object_HandPrint>(FoundActor);

				if (++CurrentIndex == HandPrint->HandPrintIndex)
				{
					HandPrint->StartCongCong(NextCong);
				}

				if (CurrentIndex >= MaxIndex)
				{
					GetWorld()->GetTimerManager().ClearTimer(CongHandle);
				}
			}
		}, NextCong, true);
}

#pragma endregion