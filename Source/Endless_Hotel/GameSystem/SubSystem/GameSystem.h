// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/Anomaly/Type_AnomalyRule.h"
#include "Type/Anomaly/Type_AnomalyID.h"
#include "Type/Level/Type_Level.h"
#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <Delegates/DelegateCombinations.h>
#include <GameSystem.generated.h>

#define STARTFLOOR 9

#pragma region Declare

class AAnomaly_Generator;
class AAnomaly_Event;
class AAnomaly_Object_Base;

UENUM(BlueprintType)
enum class EAnomalyVerdictMode : uint8
{
	Both_AND,
	Normal
};

USTRUCT(BlueprintType)
struct FAnomalyObjectArray
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<TObjectPtr<AAnomaly_Object_Base>> Objects;
};

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API UGameSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

#pragma region Base

public:
	UGameSystem();

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

#pragma endregion

#pragma region Data Layer

private:
	UFUNCTION()
	void OnChangedDataLayer(const EMapDataLayer& DataLayer);

#pragma endregion

#pragma region AnomalyState

public:
	void SetIsAnomalySolved(bool bIsSolved) { bIsAnomalySolved = bIsSolved; }
	void SetIsElevatorNormal(bool bIsNormal) { bIsElevatorNormal = bIsNormal; }

private:
	bool bIsAnomalySolved = false;
	bool bIsElevatorNormal = false;

#pragma endregion

#pragma region Floor

private:
	void ResetFloor() { Floor = STARTFLOOR; NextAnomalyMap = EMapDataLayer::Hotel; };
	void SubFloor();
	void AddFloor();

public:
	uint8 Floor = STARTFLOOR;
	bool bIsFirstStartFloor = true;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFloorChange_Reset);
	FOnFloorChange_Reset FloorChange_Reset;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFloorChange_Disable);
	FOnFloorChange_Disable FloorChange_Disable;

#pragma endregion

#pragma region Verdict

public:
	void SetVerdictMode(EAnomalyVerdictMode ENewMode = EAnomalyVerdictMode::Normal) { VerdictMode = ENewMode; };
	bool ComputeVerdict() const;
	void ApplyVerdict();
	void TryInteractSolveVerdict();

public:
	EAnomalyVerdictMode VerdictMode;

	bool bPassed = false;

#pragma endregion

#pragma region Anomaly

public:
	void SetCurrentAnomaly(AAnomaly_Event* Anomaly, EAnomalyID AnomalyID, EMapDataLayer AnomalyMap);
	void SetNextAnomaly(EAnomalyID AnomalyID, EMapDataLayer AnomalyMap);
	void LoadNextMap();
	bool IsAnomalyReady() { return bIsAnomalyReady; }

public:
	uint8 AnomalyCount = 0;

	TObjectPtr<class AAnomaly_Event> CurrentAnomaly;
	EAnomalyID CurrentAnomalyID = EAnomalyID::None;
	EAnomalyID NextAnomalyID = EAnomalyID::None;

	EMapDataLayer NextAnomalyMap = EMapDataLayer::Hotel;
	EMapDataLayer CurrentDataLayer;

	TArray<EAnomalyRule> AnomalyRules = { EAnomalyRule::EightExit };
	
	bool bIsStartInBed = false;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnomalySpawned);
	FAnomalySpawned OnAnomalySpawned;

private:
	bool bIsAnomalyReady = false;

#pragma endregion

#pragma region Pool

public:
	void InitializePool();
	void RegisterAnomalyObject(AAnomaly_Object_Base* Object);
	void UnRegisterAnomalyObject(AAnomaly_Object_Base* Object);
	void AddAnomalyRule(const EAnomalyRule& AnomalyRule);
	void RemoveAnomalyRule(const EAnomalyRule& AnomalyRule);
	TMap<TObjectPtr<UClass>, FAnomalyObjectArray> GetAnomalyObject() { return AnomalyObjectPool; }

public:
	uint8 ActIndex = 0;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddAnomalyRule, EAnomalyRule, Rule);
	FOnAddAnomalyRule OnAddAnomalyRule;

private:
	UPROPERTY()
	TMap<TObjectPtr<UClass>, FAnomalyObjectArray> AnomalyObjectPool;

#pragma endregion

#pragma region Clear

public:
	UFUNCTION()
	void GameClear();

public:
	bool bIsClear = false;
	bool bExceptClearedAnomaly = false;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameClearEvent);
	FGameClearEvent GameClearEvent;

#pragma endregion

#pragma region Choose

public:
	uint8 ChooseKeyIndex = 0;

#pragma endregion

#pragma region Elevator

public:
	void RegisterElevator(class AElevator* Elevator);
	void UnRegisterElevator(FName ElevatorID);
	void SetTargetElevator();
	void RemoveTargetElevator();

	void SetPlayerinElevatorTransform(const FVector& PlayerLocation, const FRotator& PlayerRotation, const FRotator& Offset)
	{ RelativePlayerLocation = PlayerLocation; RelativePlayerRotation = PlayerRotation; ElevatorOffset = Offset; }
	void SetPlayerVelocity(float InputHorizontalVelocity) { PlayerVelocity = InputHorizontalVelocity; }

	AElevator* GetElevatorByID(FName TargetID);

	float GetPlayerVelocity() { return PlayerVelocity; }
	FVector GetPlayerinElevatorLocation() { return RelativePlayerLocation; }
	FRotator GetPlayerinElevatorRotation() { return RelativePlayerRotation; }

	FRotator GetElevatorOffset() { return ElevatorOffset; }
	bool IsTargetElevator(const AElevator* Elevator);

private:
	FVector RelativePlayerLocation;
	FRotator RelativePlayerRotation;
	FRotator ElevatorOffset;
	TMap<FName, TWeakObjectPtr<class AElevator>> Elevators;
	TWeakObjectPtr<class AElevator> TargetElevator = nullptr;
	float PlayerVelocity;

#pragma endregion

#pragma region Reset

public:
	void ResetGameSystem();

#pragma endregion

};