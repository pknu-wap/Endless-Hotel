// Copyright by 2026-1 WAP Game 2 team

#include "GameSystem.h"

#include "GameSystem/SubSystem/AnomalyPoolSubsystem.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include "GameSystem/SubSystem/DataLayerStreamingSubsystem.h"
#include "GameSystem/SubSystem/ElevatorManagerSubsystem.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include <Engine/GameInstance.h>
#include <Math/UnrealMathUtility.h>

#pragma region Base

void UGameSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Collection.InitializeDependency<UFloorProgressSubsystem>();
	Collection.InitializeDependency<UDataLayerStreamingSubsystem>();
	Collection.InitializeDependency<UAnomalyPoolSubsystem>();
	Collection.InitializeDependency<UAnomalyVerdictSubsystem>();
	Collection.InitializeDependency<UElevatorManagerSubsystem>();

	ChooseKeyIndex = FMath::RandRange(1, 2);
}

#pragma endregion

#pragma region Reset

void UGameSystem::ResetGameSystem()
{
	UGameInstance* GameInstance = GetGameInstance();
	if (!GameInstance)
	{
		return;
	}

	if (UFloorProgressSubsystem* FloorSys = GameInstance->GetSubsystem<UFloorProgressSubsystem>())
	{
		FloorSys->ResetFloorProgress();
	}

	if (UDataLayerStreamingSubsystem* DataLayerSys = GameInstance->GetSubsystem<UDataLayerStreamingSubsystem>())
	{
		DataLayerSys->ResetDataLayerState();
	}

	if (UAnomalyVerdictSubsystem* VerdictSys = GameInstance->GetSubsystem<UAnomalyVerdictSubsystem>())
	{
		VerdictSys->ResetVerdict();
	}

	if (UElevatorManagerSubsystem* ElevatorSys = GameInstance->GetSubsystem<UElevatorManagerSubsystem>())
	{
		ElevatorSys->ResetElevatorState();
	}

	if (UAnomalyPoolSubsystem* PoolSys = GameInstance->GetSubsystem<UAnomalyPoolSubsystem>())
	{
		PoolSys->ResetPool();
	}
}

#pragma endregion