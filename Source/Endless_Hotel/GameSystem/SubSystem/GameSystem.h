// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/Anomaly/Type_AnomalyRule.h"
#include "Type/Anomaly/Type_AnomalyID.h"
#include "Type/Level/Type_Level.h"
#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <Delegates/DelegateCombinations.h>
#include <GameSystem.generated.h>

class AAnomaly_Generator;
class AAnomaly_Event;
class AAnomaly_Object_Base;

#define STARTFLOOR 9

#pragma region Declare

UENUM(BlueprintType)
enum class EAnomalyVerdictMode : uint8
{
	SolvedOnly,
	Both_AND,
	Normal,
	Fail
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameClearEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFloorChange_Reset);

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

private:
	bool bIsAnomalySolved = false;
	bool bIsElevatorNormal = false;

public:
	void SetIsAnomalySolved(bool bIsSolved) { bIsAnomalySolved = bIsSolved; };
	void SetIsElevatorNormal(bool bIsNormal) { bIsElevatorNormal = bIsNormal; };

#pragma endregion

#pragma region Floor

public:
	uint8 Floor = STARTFLOOR;
	FOnFloorChange_Reset FloorChange_Reset;

private:
	void ResetFloor() { Floor = STARTFLOOR; NextAnomalyMap = EMapDataLayer::Hotel; };
	void SubFloor();
	void AddFloor();

#pragma endregion

#pragma region Verdict

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Verdict")
	EAnomalyVerdictMode VerdictMode;

	bool bPassed = false;

public:
	void SetVerdictMode(EAnomalyVerdictMode ENewMode = EAnomalyVerdictMode::Fail) { VerdictMode = ENewMode; };
	bool ComputeVerdict() const;
	void ApplyVerdict();
	void TryInteractSolveVerdict();

#pragma endregion

#pragma region Anomaly

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFloorChange_Disable);

public:
	void SetCurrentAnomaly(AAnomaly_Event* Anomaly, EAnomalyID AnomalyName, EMapDataLayer AnomalyMap);
	void SetNextAnomaly(EAnomalyID AnomalyName, EMapDataLayer AnomalyMap);
	void LoadNextMap();

public:
	UPROPERTY(BlueprintReadWrite, Category = "Anomaly|Count")
	uint8 AnomalyCount = 0;

	UPROPERTY(EditAnywhere, Category = "Anomaly")
	TObjectPtr<class AAnomaly_Event> CurrentAnomaly;

	UPROPERTY(BlueprintReadOnly, Category = "Anomaly")
	EAnomalyID NextAnomalyID = EAnomalyID::None;

	UPROPERTY(BlueprintReadOnly, Category = "Anomaly")
	EMapDataLayer NextAnomalyMap = EMapDataLayer::Hotel;

	TArray<EAnomalyRule> AnomalyRules = { EAnomalyRule::EightExit };
	FOnFloorChange_Disable FloorChange_Disable;
	EMapDataLayer CurrentDataLayer;
	bool bIsStartInBed = false;

#pragma endregion

#pragma region Pool

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly|Pool")
	uint8 ActIndex = 0;

private:
	UPROPERTY()
	TMap<TObjectPtr<UClass>, FAnomalyObjectArray> AnomalyObjectPool;

public:
	void InitializePool();
	void RegisterAnomalyObject(AAnomaly_Object_Base* Object);
	void UnRegisterAnomalyObject(AAnomaly_Object_Base* Object);
	TMap<TObjectPtr<UClass>, FAnomalyObjectArray> GetAnomalyObject() { return AnomalyObjectPool; };

#pragma endregion

#pragma region Clear

public:
	UFUNCTION()
	void GameClear();

public:
	bool bIsClear = false;
	bool bExceptClearedAnomaly = false;
	FGameClearEvent GameClearEvent;

#pragma endregion

#pragma region Choose

public:
	int32 ChooseKeyIndex = 0;

#pragma endregion

#pragma region Elevator

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnomalySpawned);

public:
	void RegisterElevator(class AElevator* Elevator);
	void UnRegisterElevator(FName ElevatorID);
	void SetTargetElevator();
	void RemoveTargetElevator();
	void SetPlayerinElevatorTransform(const FVector& PlayerLocation, const FRotator& PlayerRotation, const FRotator& Offset)
	{ RelativePlayerLocation = PlayerLocation; RelativePlayerRotation = PlayerRotation; ElevatorOffset = Offset; };
	void SetPlayerVelocity(float InputHorizontalVelocity) { PlayerVelocity = InputHorizontalVelocity; }

	AElevator* GetElevatorByID(FName TargetID);
	float GetPlayerVelocity() { return PlayerVelocity; }
	FVector GetPlayerinElevatorLocation() { return RelativePlayerLocation; }
	FRotator GetPlayerinElevatorRotation() { return RelativePlayerRotation; }
	FRotator GetElevatorOffset() { return ElevatorOffset; }
	FTransform GetPlayerinElevatorTransform() { return RelativePlayerTransform; };
	bool IsTargetElevator(const AElevator* Elevator);

public:
	FAnomalySpawned OnAnomalySpawned;

private:
	FVector RelativePlayerLocation;
	FRotator RelativePlayerRotation;
	FRotator ElevatorOffset;
	FTransform RelativePlayerTransform;
	TMap<FName, TWeakObjectPtr<class AElevator>> Elevators;
	TWeakObjectPtr<class AElevator> TargetElevator = nullptr;
	float PlayerVelocity;

#pragma endregion

};