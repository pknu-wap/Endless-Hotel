// Copyright by 2026-1 WAP Game 2 team

#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include <Engine/GameInstance.h>

#pragma region Base

UFloorProgressSubsystem::UFloorProgressSubsystem()
{
	FloorChange_Reset.AddUObject(this, &ThisClass::ProgressGameState);
}

void UFloorProgressSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Collection.InitializeDependency<UAnomalyVerdictSubsystem>();
	Floor = STARTFLOOR;
}

#pragma endregion

#pragma region Floor

void UFloorProgressSubsystem::SubFloor()
{
	if (Floor > 1)
	{
		Floor--;
		return;
	}
	const auto* GameSys = GetGameInstance()->GetSubsystem<UGameSystem>();
	GameSys->GameClearEvent.Broadcast();
}

void UFloorProgressSubsystem::AddFloor()
{
	if (Floor < STARTFLOOR)
	{
		Floor++;
	}
}

void UFloorProgressSubsystem::AdvanceFloor(const bool bPassed)
{
	const auto* GameSys = GetGameInstance()->GetSubsystem<UGameSystem>();
	const bool bCheckIn = GameSys->GetGameProgression() == EGameProgression::CheckIn;
	if (!bCheckIn)
	{
		bIsFirstStartFloor = false;
	}
	if (!bPassed)
	{
		ResetFloor();
		return;
	}
	bCheckIn ? AddFloor() : SubFloor();
}

#pragma endregion

#pragma region Clear

#pragma endregion

#pragma region Reset

void UFloorProgressSubsystem::ResetFloorProgress()
{
	Floor = STARTFLOOR;
	bIsFirstStartFloor = true;
}

#pragma endregion

#pragma region Progression

void UFloorProgressSubsystem::ProgressGameState()
{
	if (bFirstReset)
	{
		bFirstReset = false;
		return;
	}

	FSaveData_Progression Data = USaveManager::LoadData_Progression();
	if (Data.Progression == EGameProgression::Tutorial)
	{
		auto* GameSystem = GetGameInstance()->GetSubsystem<UGameSystem>();
		GameSystem->ChangeProgression(EGameProgression::Loop);
	}
}

#pragma endregion