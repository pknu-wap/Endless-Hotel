// Copyright by 2026-1 WAP Game 2 team

#include "Component/Elevator/ElevatorVerdictComponent.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include <Engine/GameInstance.h>
#include <Engine/World.h>

#pragma region Verdict

void UElevatorVerdictComponent::RequestVerdict() const
{
	const auto* GI = GetWorld()->GetGameInstance();
	auto* VerdictSub = GI->GetSubsystem<UAnomalyVerdictSubsystem>();
	VerdictSub->SetIsElevatorNormal(bIsNormalElevator);
	VerdictSub->TryInteractSolveVerdict();
	VerdictSub->ApplyVerdict();
}

#pragma endregion