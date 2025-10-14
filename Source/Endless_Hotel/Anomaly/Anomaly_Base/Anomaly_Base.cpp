// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Anomaly_Base/Anomaly_Base.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"
#include "Engine/GameInstance.h"

#pragma region Base

AAnomaly_Base::AAnomaly_Base(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	AnomalyID = -1;
	bIsActive = false;
}

#pragma endregion

#pragma region Activities
void AAnomaly_Base::ActivateAnomaly_Implementation()
{
	bIsActive = true;
}
#pragma endregion

#pragma region Verdicts

void AAnomaly_Base::SetSolved(bool bNewSolved)
{
	if (bNewSolved)
		MarkSolved();
	else
		MarkFailed();
}

void AAnomaly_Base::SetVerdictMode(EAnomalyVerdictMode NewMode)
{
	auto* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
	Sub->SetVerdictMode(NewMode); // VerdictMode Setting
}

#pragma endregion

#pragma region Inner Verdicts

void AAnomaly_Base::FinalizeAnomaly(bool bPassed)
{
	if (bPassed)	MarkSolved();
	else			MarkFailed();

	bIsActive = false;
}

void AAnomaly_Base::MarkSolved()
{
	auto* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
	Sub->SetIsAnomalySolved(true);
}

void AAnomaly_Base::MarkFailed()
{
	auto* Sub = GetGameInstance()->GetSubsystem<UAnomalyProgressSubSystem>();
	Sub->SetIsAnomalySolved(false);
}

#pragma endregion