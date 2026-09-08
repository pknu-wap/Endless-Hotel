// Copyright by 2026-1 WAP Game 2 team

#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include "Asset/Manager/EHAssetManager.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/SubSystem/AnomalyPoolSubsystem.h"
#include "GameSystem/SubSystem/DataLayerStreamingSubsystem.h"
#include "GameSystem/SubSystem/ElevatorManagerSubsystem.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include "Anomaly/Event/Anomaly_Event.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Character.h>
#include <Engine/World.h>
#include <Engine/GameInstance.h>

#pragma region Base

void UAnomalyVerdictSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Collection.InitializeDependency<UAnomalyPoolSubsystem>();
	Collection.InitializeDependency<UDataLayerStreamingSubsystem>();
	Collection.InitializeDependency<UElevatorManagerSubsystem>();
	Collection.InitializeDependency<UFloorProgressSubsystem>();

	if (UDataLayerStreamingSubsystem* DataLayerSys = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDataLayerStreamingSubsystem>() : nullptr)
	{
		DataLayerSys->OnDataLayerReady.AddUObject(this, &ThisClass::OnDataLayerReady);
	}
}

#pragma endregion

#pragma region Verdict

bool UAnomalyVerdictSubsystem::ComputeVerdict() const
{
	switch (VerdictMode)
	{
	case EAnomalyVerdictMode::Both_AND:
		return bIsAnomalySolved && !bIsElevatorNormal;
	case EAnomalyVerdictMode::Normal:
		return bIsAnomalySolved && bIsElevatorNormal;
	default:
		return false;
	}
}

void UAnomalyVerdictSubsystem::EvaluateIncorrectRules()
{
	switch (VerdictMode)
	{
	case EAnomalyVerdictMode::Both_AND:
		if (bIsElevatorNormal)
		{
			IncorrectRules.AddUnique(EAnomalyRule::EightExit);
		}
		break;
	case EAnomalyVerdictMode::Normal:
		if (!bIsElevatorNormal)
		{
			IncorrectRules.AddUnique(EAnomalyRule::EightExit);
		}
		break;
	default:
		break;
	}

	if (!bIsAnomalySolved && CurrentAnomaly)
	{
		IncorrectRule = CurrentAnomaly->Rule;
		IncorrectRules.AddUnique(CurrentAnomaly->Rule);
	}
	if (bWrongInteractionOccurred)
	{
		IncorrectRules.AddUnique(EAnomalyRule::Touch);
	}

	OnOccurIncorrectRule.Broadcast(IncorrectRules);
}

void UAnomalyVerdictSubsystem::ApplyVerdict()
{
	auto& AssetManager = UEHAssetManager::Get();
	IncorrectRules.Empty();
	bPassed = ComputeVerdict() && !bWrongInteractionOccurred;

	UFloorProgressSubsystem* FloorSys = GetGameInstance() ? GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>() : nullptr;
	UAnomalyPoolSubsystem* PoolSys = GetGameInstance() ? GetGameInstance()->GetSubsystem<UAnomalyPoolSubsystem>() : nullptr;

	if (bPassed)
	{
		if (FloorSys)
		{
			FloorSys->SubFloor();
		}
		bIsStartInBed = false;

		if (PoolSys && PoolSys->bExceptClearedAnomaly)
		{
			AssetManager.MarkAnomalyCleared(CurrentAnomaly->AnomalyID);
			USaveManager::SaveClearedAnomalyID(AssetManager.GetClearedAnomalySet());
		}
		PoolSys->ClearFakeManualEntry(CurrentAnomaly->AnomalyID);
	}
	else
	{
		if (bSuperCowardMode)
		{
			EvaluateIncorrectRules();
		}
		if (FloorSys)
		{
			FloorSys->ResetFloor();
		}
		NextAnomalyMap = EMapDataLayer::Hotel;
	}

	bIsAnomalySolved = false;
	bWrongInteractionOccurred = false;
	if (FloorSys)
	{
		FloorSys->bIsFirstStartFloor = false;
	}

	LoadNextMap();
}

void UAnomalyVerdictSubsystem::TryInteractSolveVerdict()
{
	if (bWrongInteractionOccurred)
	{
		return;
	}
	if (AAnomaly_Event* Neo = Cast<AAnomaly_Event>(CurrentAnomaly))
	{
		Neo->InteractSolveVerdict();
	}
}

#pragma endregion

#pragma region Anomaly

void UAnomalyVerdictSubsystem::SetCurrentAnomaly(AAnomaly_Event* Anomaly, EAnomalyID AnomalyID, EMapDataLayer AnomalyMap)
{
	CurrentAnomaly = Anomaly;
	CurrentAnomalyID = AnomalyID;
	CurrentAnomaly->AnomalyID = AnomalyID;

	UDataLayerStreamingSubsystem* DataLayerSys = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDataLayerStreamingSubsystem>() : nullptr;
	if (DataLayerSys)
	{
		DataLayerSys->SetCurrentDataLayer(AnomalyMap);
	}

	UElevatorManagerSubsystem* ElevatorSys = GetGameInstance() ? GetGameInstance()->GetSubsystem<UElevatorManagerSubsystem>() : nullptr;
	if (ElevatorSys)
	{
		ElevatorSys->SetTargetElevator(CurrentAnomaly->TargetElevatorID);
	}

	CurrentAnomaly->SetAnomalyState();

	if (CurrentAnomaly->AnomalyID != EAnomalyID::Normal)
	{
		if (UAnomalyPoolSubsystem* PoolSys = GetGameInstance() ? GetGameInstance()->GetSubsystem<UAnomalyPoolSubsystem>() : nullptr)
		{
			++PoolSys->ActIndex;
		}
	}

	if (ElevatorSys)
	{
		ElevatorSys->StartAllElevator();
	}
}

void UAnomalyVerdictSubsystem::SetNextAnomaly(EAnomalyID AnomalyID, EMapDataLayer AnomalyMap)
{
	NextAnomalyID = AnomalyID;
	NextAnomalyMap = AnomalyMap;
}

void UAnomalyVerdictSubsystem::LoadNextMap()
{
	UDataLayerStreamingSubsystem* DataLayerSys = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDataLayerStreamingSubsystem>() : nullptr;
	UFloorProgressSubsystem* FloorSys = GetGameInstance() ? GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>() : nullptr;

	if (FloorSys)
	{
		FloorSys->FloorChange_Disable.Broadcast();
	}

	UEHGameInstance* GameInstance = GetWorld()->GetGameInstance<UEHGameInstance>();
	const bool bLayerChanged = GameInstance->SwitchDataLayer(NextAnomalyMap);

	if (!bLayerChanged && FloorSys)
	{
		FloorSys->FloorChange_Reset.Broadcast();
	}
}

void UAnomalyVerdictSubsystem::OnDataLayerReady()
{
	UFloorProgressSubsystem* FloorSys = GetGameInstance() ? GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>() : nullptr;

	if (FloorSys && FloorSys->bIsFirstStartFloor)
	{
		bIsStartInBed = true;
	}

	if (FloorSys)
	{
		FloorSys->FloorChange_Reset.Broadcast();
	}
}

#pragma endregion

#pragma region Reset

void UAnomalyVerdictSubsystem::ResetVerdict()
{
	bPassed = false;
	bIsAnomalySolved = false;
	bIsElevatorNormal = false;

	CurrentAnomaly = nullptr;
	CurrentAnomalyID = EAnomalyID::None;
	NextAnomalyID = EAnomalyID::None;
	NextAnomalyMap = EMapDataLayer::Hotel;
	bIsStartInBed = false;
	IncorrectRule = EAnomalyRule::None;
	IncorrectRules.Empty();
}

#pragma endregion