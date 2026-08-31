// Copyright by 2026-1 WAP Game 2 team

#include "GameSystem/SubSystem/FloorProgressSubsystem.h"

#include "GameSystem/SaveGame/SaveManager.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include <Engine/GameInstance.h>

#pragma region Base

UFloorProgressSubsystem::UFloorProgressSubsystem()
{
	GameClearEvent.AddDynamic(this, &ThisClass::GameClear);
}

void UFloorProgressSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Collection.InitializeDependency<UAnomalyVerdictSubsystem>();

	Floor = STARTFLOOR;
	bIsClear = USaveManager::LoadData_Progression().bGameClear;
}

#pragma endregion

#pragma region Floor

void UFloorProgressSubsystem::ResetFloor()
{
	Floor = STARTFLOOR;

	if (UAnomalyVerdictSubsystem* VerdictSys = GetGameInstance() ? GetGameInstance()->GetSubsystem<UAnomalyVerdictSubsystem>() : nullptr)
	{
		VerdictSys->NextAnomalyMap = EMapDataLayer::Hotel;
	}
}

void UFloorProgressSubsystem::SubFloor()
{
	if (Floor > 1)
	{
		Floor--;
	}
	else
	{
		GameClearEvent.Broadcast();
	}
}

void UFloorProgressSubsystem::AddFloor()
{
	if (Floor < STARTFLOOR)
	{
		Floor++;
	}
}

#pragma endregion

#pragma region Clear

void UFloorProgressSubsystem::GameClear()
{
	bIsClear = true;
	Floor = STARTFLOOR;

	FSaveData_Progression Data = USaveManager::LoadData_Progression();
	Data.bGameClear = true;
	USaveManager::SaveData_Progression(Data);
}

#pragma endregion

#pragma region Reset

void UFloorProgressSubsystem::ResetFloorProgress()
{
	Floor = STARTFLOOR;
	bIsFirstStartFloor = true;

	bIsClear = USaveManager::LoadData_Progression().bGameClear;
}

#pragma endregion
