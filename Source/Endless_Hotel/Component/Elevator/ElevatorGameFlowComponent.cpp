// Copyright by 2026-1 WAP Game 2 team

#include "Component/Elevator/ElevatorGameFlowComponent.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include "GameSystem/SubSystem/ElevatorManagerSubsystem.h"
#include "GameSystem/SubSystem/GameSystem.h"

#pragma region Verdict

void UElevatorGameFlowComponent::RequestVerdict() const
{
	const auto* GI = GetWorld()->GetGameInstance();
	auto* VerdictSub = GI->GetSubsystem<UAnomalyVerdictSubsystem>();
	VerdictSub->SetIsElevatorNormal(bIsNormalElevator);
	VerdictSub->TryInteractSolveVerdict();
	VerdictSub->ApplyVerdict();
}

#pragma endregion

#pragma region Floor

void UElevatorGameFlowComponent::ScriptFloor() const
{
	const auto* GI = GetWorld()->GetGameInstance();
	auto* FloorSys = GI->GetSubsystem<UFloorProgressSubsystem>();
	FloorSys->AdvanceScriptedFloor();
}

bool UElevatorGameFlowComponent::IsTopFloor() const
{
	const auto* GI = GetWorld()->GetGameInstance();
	const auto* FloorSys = GI->GetSubsystem<UFloorProgressSubsystem>();
	return FloorSys->IsTopFloor();
}

#pragma endregion

#pragma region DataLayer

void UElevatorGameFlowComponent::RequestSwapDataLayer(const EMapDataLayer InLayer) const
{
	auto* GI = GetWorld()->GetGameInstance<UEHGameInstance>();
	GI->SwitchDataLayer(InLayer);
}

#pragma endregion

#pragma region Progression

bool UElevatorGameFlowComponent::IsCheckIn() const
{
	const auto* GI = GetWorld()->GetGameInstance();
	const auto* GameSys = GI->GetSubsystem<UGameSystem>();
	return GameSys && GameSys->GetGameProgression() == EGameProgression::CheckIn;
}

#pragma endregion

#pragma region Target

void UElevatorGameFlowComponent::SetTargetElevator(const FName InElevatorID) const
{
	const auto* GI = GetWorld()->GetGameInstance();
	auto* ElevatorSub = GI->GetSubsystem<UElevatorManagerSubsystem>();
	ElevatorSub->SetTargetElevator(InElevatorID);
}

#pragma endregion