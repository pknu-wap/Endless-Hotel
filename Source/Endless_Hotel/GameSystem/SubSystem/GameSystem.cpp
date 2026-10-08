// Copyright by 2026-1 WAP Game 2 team

#include "GameSystem/SubSystem/GameSystem.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include "GameSystem/SubSystem/DataLayerStreamingSubsystem.h"
#include "GameSystem/SubSystem/AnomalyPoolSubsystem.h"
#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include "GameSystem/SubSystem/AnomalyGeneratorSubsystem.h"
#include "GameSystem/SubSystem/ElevatorManagerSubsystem.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include <Engine/GameInstance.h>
#include <Math/UnrealMathUtility.h>

#include "Asset/Manager/EHAssetManager.h"

#pragma region Base

void UGameSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	Collection.InitializeDependency<UFloorProgressSubsystem>();
	Collection.InitializeDependency<UDataLayerStreamingSubsystem>();
	Collection.InitializeDependency<UAnomalyPoolSubsystem>();
	Collection.InitializeDependency<UAnomalyVerdictSubsystem>();
	Collection.InitializeDependency<UAnomalyGeneratorSubsystem>();
	Collection.InitializeDependency<UElevatorManagerSubsystem>();

	ChooseKeyIndex = FMath::RandRange(1, 2);
	
	GameClearEvent.AddUObject(this, &UGameSystem::GameClear);
}

#pragma endregion

#pragma region Reset

void UGameSystem::ResetGameSystem() const
{
	const UGameInstance* GameInstance = GetGameInstance();
	if (!GameInstance)
	{
		return;
	}

	if (UDataLayerStreamingSubsystem* DataLayerSys = GameInstance->GetSubsystem<UDataLayerStreamingSubsystem>())
	{
		DataLayerSys->ResetDataLayerState();
	}

	if (UAnomalyVerdictSubsystem* VerdictSys = GameInstance->GetSubsystem<UAnomalyVerdictSubsystem>())
	{
		VerdictSys->ResetVerdict(USaveManager::LoadData_Progression().Progression == EGameProgression::CheckIn);
	}

	if (UElevatorManagerSubsystem* ElevatorSys = GameInstance->GetSubsystem<UElevatorManagerSubsystem>())
	{
		ElevatorSys->ResetElevatorState();
	}

	if (UAnomalyPoolSubsystem* PoolSys = GameInstance->GetSubsystem<UAnomalyPoolSubsystem>())
	{
		PoolSys->ResetPool();
	}
	
	if (UAnomalyGeneratorSubsystem* GeneratorSys = GameInstance->GetSubsystem<UAnomalyGeneratorSubsystem>())
	{
		GeneratorSys->ResetGenerator();
	}
	
	if (UFloorProgressSubsystem* FloorSys = GameInstance->GetSubsystem<UFloorProgressSubsystem>())
	{
		FloorSys->ResetFloorProgress();
	}
}

#pragma endregion

#pragma region Progression

void UGameSystem::ChangeProgression(const EGameProgression Target)
{
	FSaveData_Progression Data = USaveManager::LoadData_Progression();
	Data.Progression = Target;
	USaveManager::SaveData_Progression(Data);
	GameProgression = Target;
	OnProgressionChanged.Broadcast(Target);
}

#pragma endregion

#pragma region Clear

void UGameSystem::GameClear()
{
	const auto& AssetManager = UEHAssetManager::Get();
	const EGameProgression Ending = AssetManager.GetRemainingAnomalyCounts() == 0 ? EGameProgression::Clear_True : EGameProgression::Clear_Bad;
	ChangeProgression(Ending);
}

bool UGameSystem::IsGameClear() const
{
	const FSaveData_Progression Data = USaveManager::LoadData_Progression();
	return Data.Progression == EGameProgression::Clear_True || Data.Progression == EGameProgression::Clear_Bad;
}

#pragma endregion