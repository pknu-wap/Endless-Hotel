// Copyright by 2025-2 WAP Game 2 team

#include "Anomaly/Base/Anomaly_Base.h"
#include "GameSystem/SubSystem/AnomalyProgressSubSystem.h"
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include <Engine/GameInstance.h>
#include <Kismet/GameplayStatics.h>

#pragma region Base

AAnomaly_Base::AAnomaly_Base(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AnomalyID = -1;
}

#pragma endregion

#pragma region Anomaly

void AAnomaly_Base::StartAnomalyAction()
{
	for (auto* FoundActor : LinkedObjects)
	{
		auto* AnomalyObject = Cast<AAnomaly_Object_Base>(FoundActor);
		AnomalyAction(AnomalyObject);
	}
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