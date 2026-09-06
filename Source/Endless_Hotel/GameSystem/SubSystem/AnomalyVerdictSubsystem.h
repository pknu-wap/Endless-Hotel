// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Type/Anomaly/Type_AnomalyID.h"
#include "Type/Anomaly/Type_AnomalyRule.h"
#include "Type/Level/Type_Level.h"
#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <AnomalyVerdictSubsystem.generated.h>

#pragma region Declare

class AAnomaly_Event;

UENUM(BlueprintType)
enum class EAnomalyVerdictMode : uint8
{
	Both_AND,
	Normal
};

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API UAnomalyVerdictSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

#pragma region Base

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

#pragma endregion

#pragma region AnomalyState

public:
	void SetIsAnomalySolved(bool bIsSolved) { bIsAnomalySolved = bIsSolved; }
	void SetIsElevatorNormal(bool bIsNormal) { bIsElevatorNormal = bIsNormal; }

private:
	bool bIsAnomalySolved = false;
	bool bIsElevatorNormal = false;

#pragma endregion

#pragma region Verdict

public:
	void SetVerdictMode(EAnomalyVerdictMode ENewMode = EAnomalyVerdictMode::Normal) { VerdictMode = ENewMode; };
	bool ComputeVerdict() const;
	void ApplyVerdict();
	void TryInteractSolveVerdict();

private:
	void EvaluateIncorrectRules();

public:
	EAnomalyVerdictMode VerdictMode = EAnomalyVerdictMode::Normal;
	bool bPassed = false;
	bool bWrongInteractionOccurred = false;
	bool bSuperCowardMode = true;	// 임시 이름

#pragma endregion

#pragma region Anomaly

public:
	void SetCurrentAnomaly(AAnomaly_Event* Anomaly, EAnomalyID AnomalyID, EMapDataLayer AnomalyMap);
	void SetNextAnomaly(EAnomalyID AnomalyID, EMapDataLayer AnomalyMap);
	void LoadNextMap();
	void OnDataLayerReady();
	bool IsAnomalyReady() const { return bIsAnomalyReady; }

	AAnomaly_Event* GetCurrentAnomaly() const { return CurrentAnomaly; }
	EAnomalyID GetCurrentAnomalyID() const { return CurrentAnomalyID; }
	EMapDataLayer GetNextAnomalyMap() const { return NextAnomalyMap; }

	EAnomalyRule GetIncorrectRule() const { return IncorrectRule; }
	TArray<EAnomalyRule> GetIncorrectRules() const { return IncorrectRules; }

public:
	TObjectPtr<AAnomaly_Event> CurrentAnomaly;
	EAnomalyID CurrentAnomalyID = EAnomalyID::None;
	EAnomalyID NextAnomalyID = EAnomalyID::None;

	EMapDataLayer NextAnomalyMap = EMapDataLayer::Hotel;

	bool bIsStartInBed = false;

	DECLARE_MULTICAST_DELEGATE(FAnomalySpawned);
	FAnomalySpawned OnAnomalySpawned;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOccurIncorrectRule, TArray<EAnomalyRule>);
	FOccurIncorrectRule OnOccurIncorrectRule;

private:
	bool bIsAnomalyReady = false;
	EAnomalyRule IncorrectRule = EAnomalyRule::None;
	TArray<EAnomalyRule> IncorrectRules;

#pragma endregion

#pragma region Reset

public:
	void ResetVerdict();

#pragma endregion

};