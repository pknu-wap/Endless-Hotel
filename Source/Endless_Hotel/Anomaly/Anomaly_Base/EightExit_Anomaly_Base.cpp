// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Anomaly_Base/EightExit_Anomaly_Base.h"

#pragma region Anomaly Active& DeActive

void AEightExit_Anomaly_Base::ActivateAnomaly_Implementation()
{
	Super::ActivateAnomaly_Implementation();
}

#pragma endregion

#pragma region Anomaly Verdict

void AEightExit_Anomaly_Base::SetIsSolved(bool bIsCorrectElevator)
{
	if (bIsCorrectElevator)
	{
		Super::IsSolveAnomaly();
	}
	else
	{
		Super::IsNotSolveAnomaly();
	}
}

#pragma endregion