// Copyright by 2025-2 WAP Game 2 team


#include "Anomaly/Anomaly_Base/Neapolitan_Anomaly_Base.h"

#pragma region Anomaly Active& DeActive

void ANeapolitan_Anomaly_Base::ActivateAnomaly_Implementation()
{
	Super::ActivateAnomaly_Implementation();
}

#pragma endregion

#pragma region Anomaly Verdict

void ANeapolitan_Anomaly_Base::SetIsSolved(bool bIsSolved, bool bIsCorrectElevator)
{
	if (bIsSolved && bIsCorrectElevator)
	{
		Super::IsSolveAnomaly();
	}
	else
	{
		Super::IsNotSolveAnomaly();
	}
}

#pragma endregion