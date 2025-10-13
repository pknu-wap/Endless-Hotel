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
	bIsSolved = bNewSolved;
}

void AAnomaly_Base::SetCorrectElevator(bool bNewCorrect)
{
	bIsCorrectElevator = bNewCorrect;
}

bool AAnomaly_Base::SubmitVerdictWith(bool bSolved, bool bCorrectElevator)
{
	bIsSolved = bSolved;
	bIsCorrectElevator = bCorrectElevator;

	SubmitVerdict();

	return EvaluateOutcome();
}

void AAnomaly_Base::SubmitVerdict()
{
	const bool bPassed = EvaluateOutcome();
	FinalizeAnomaly(bPassed);
}

#pragma endregion

#pragma region Inner Verdicts

bool AAnomaly_Base::EvaluateOutcome() const
{
	switch (VerdictMode)
	{
	case EAnomalyVerdictMode::CorrectElevatorOnly:
		return bIsCorrectElevator;

	case EAnomalyVerdictMode::SolvedOnly:
		return bIsSolved;

	case EAnomalyVerdictMode::Both_AND:
		return (bIsSolved && bIsCorrectElevator);

	case EAnomalyVerdictMode::Either_OR:
		return (bIsSolved || bIsCorrectElevator);

	default:
		return false;
	}
}

void AAnomaly_Base::FinalizeAnomaly(bool bPassed)
{
	if (bPassed)	MarkSolved();
	else			MarkFailed();

	// Subsystem에 결과 반영
	PushVerdict();

	// 한 번 처리된 뒤엔 비활성화(원하면 유지)
	bIsActive = false;
}

void AAnomaly_Base::MarkSolved()
{
	if (UGameInstance* GI = GetGameInstance())
	{
		if (auto* Sub = GI->GetSubsystem<UAnomalyProgressSubSystem>())
		{
			Sub->SetIsAnomalySolved(true);
		}
	}
}

void AAnomaly_Base::MarkFailed()
{
	if (UGameInstance* GI = GetGameInstance())
	{
		if (auto* Sub = GI->GetSubsystem<UAnomalyProgressSubSystem>())
		{
			Sub->SetIsAnomalySolved(false);
		}
	}
}

void AAnomaly_Base::PushVerdict()
{
	if (UGameInstance* GI = GetGameInstance())
	{
		if (auto* Sub = GI->GetSubsystem<UAnomalyProgressSubSystem>())
		{
			Sub->AnomalyVerdict();
		}
	}
}

#pragma endregion