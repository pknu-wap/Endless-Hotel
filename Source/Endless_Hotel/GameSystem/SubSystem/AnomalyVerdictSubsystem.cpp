// Copyright by 2026-1 WAP Game 2 team

#include "GameSystem/SubSystem/AnomalyVerdictSubsystem.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "GameSystem/SubSystem/AnomalyPoolSubsystem.h"
#include "GameSystem/SubSystem/AnomalyGeneratorSubsystem.h"
#include "GameSystem/SubSystem/DataLayerStreamingSubsystem.h"
#include "GameSystem/SubSystem/ElevatorManagerSubsystem.h"
#include "GameSystem/SubSystem/FloorProgressSubsystem.h"
#include "GameSystem/SubSystem/GameSystem.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Asset/Manager/EHAssetManager.h"
#include "Anomaly/Event/Anomaly_Event.h"
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
	case EAnomalyVerdictMode::Both_And:
		return bIsAnomalySolved && !bIsElevatorNormal;
	case EAnomalyVerdictMode::Normal:
		return bIsAnomalySolved && bIsElevatorNormal;
	default:
		return false;
	}
}

void UAnomalyVerdictSubsystem::EvaluateIncorrectRules()
{
	if (!CurrentAnomaly)
	{
		IncorrectRules.AddUnique(EAnomalyRule::EightExit);
	}
	switch (VerdictMode)
	{
	case EAnomalyVerdictMode::Both_And:
		if (bIsElevatorNormal)
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

void UAnomalyVerdictSubsystem::HandlePassed()
{
	bIsStartInBed = false;
	if (!IsValid(CurrentAnomaly))
	{
		return;
	}
	auto& AssetManager = UEHAssetManager::Get();
	AssetManager.MarkAnomalyCleared(CurrentAnomaly->AnomalyID);
	USaveManager::SaveClearedAnomalyID(AssetManager.GetClearedAnomalySet());
	if (auto* PoolSys = GetGameInstance()->GetSubsystem<UAnomalyPoolSubsystem>())
	{
		PoolSys->ClearFakeManualEntry(CurrentAnomaly->AnomalyID);
	}
}

void UAnomalyVerdictSubsystem::HandleFailed()
{
	if (bSuperCowardMode)
	{
		EvaluateIncorrectRules();
	}
	if (auto* Gen = GetGameInstance()->GetSubsystem<UAnomalyGeneratorSubsystem>())
	{
		Gen->ForceNormalNext();
	}
	NextAnomalyMap = EMapDataLayer::Hotel;
}

void UAnomalyVerdictSubsystem::ApplyVerdict()
{
	bPassed = ComputeVerdict() && !bWrongInteractionOccurred;
	bPassed ? HandlePassed() : HandleFailed();

	if (auto* FloorSys = GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>())
	{
		FloorSys->AdvanceFloor(bPassed);
	}
	bIsAnomalySolved = false;
	bWrongInteractionOccurred = false;
	LoadNextMap();
}

void UAnomalyVerdictSubsystem::TryInteractSolveVerdict() const
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

void UAnomalyVerdictSubsystem::SetNoAnomalyState()
{
	CurrentAnomaly = nullptr;
	CurrentAnomalyID = EAnomalyID::Normal;
	bIsAnomalySolved = true;
	const auto* GI = GetGameInstance();
	auto* DataLayerSys = GI->GetSubsystem<UDataLayerStreamingSubsystem>();
	auto* ElevatorSys = GI->GetSubsystem<UElevatorManagerSubsystem>();
	const auto* GameSys = GI->GetSubsystem<UGameSystem>();
	SetVerdictMode(EAnomalyVerdictMode::Normal);
	if (DataLayerSys)
	{
		DataLayerSys->SetCurrentDataLayer(EMapDataLayer::Hotel);
	}
	if (ElevatorSys && GameSys->GetGameProgression() != EGameProgression::CheckIn)
	{
		ElevatorSys->RemoveTargetElevator();
		if (!bIsStartInBed)
		{
			ElevatorSys->SetTargetElevator("HotelElevator");
		}
		ElevatorSys->StartAllElevator();
	}
}

void UAnomalyVerdictSubsystem::SetCurrentAnomaly(AAnomaly_Event* Anomaly, const EAnomalyID AnomalyID, const EMapDataLayer AnomalyMap)
{
	CurrentAnomaly = Anomaly;
	CurrentAnomalyID = AnomalyID;
	CurrentAnomaly->AnomalyID = AnomalyID;

	if (UDataLayerStreamingSubsystem* DataLayerSys = GetGameInstance() ? GetGameInstance()->GetSubsystem<UDataLayerStreamingSubsystem>() : nullptr)
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

void UAnomalyVerdictSubsystem::SetNextAnomaly(const EAnomalyID AnomalyID, const EMapDataLayer AnomalyMap)
{
	NextAnomalyID = AnomalyID;
	NextAnomalyMap = AnomalyMap;
}

void UAnomalyVerdictSubsystem::LoadNextMap() const
{
	auto* GI = GetWorld()->GetGameInstance<UEHGameInstance>();
	const auto* FloorSys = GI->GetSubsystem<UFloorProgressSubsystem>();

	if (FloorSys)
	{
		FloorSys->FloorChange_Disable.Broadcast();
	}

	if (const bool bLayerChanged = GI->SwitchDataLayer(NextAnomalyMap); !bLayerChanged && FloorSys)
	{
		FloorSys->FloorChange_Reset.Broadcast();
	}
}

void UAnomalyVerdictSubsystem::OnDataLayerReady()
{
	const UFloorProgressSubsystem* FloorSys = GetGameInstance() ? GetGameInstance()->GetSubsystem<UFloorProgressSubsystem>() : nullptr;

	if (FloorSys && FloorSys->GetIsFirstFloor())
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
	CurrentAnomalyID = EAnomalyID::Normal;
	NextAnomalyID = EAnomalyID::None;
	NextAnomalyMap = EMapDataLayer::Hotel;
	bIsStartInBed = false;
	IncorrectRule = EAnomalyRule::None;
	IncorrectRules.Empty();
}

#pragma endregion