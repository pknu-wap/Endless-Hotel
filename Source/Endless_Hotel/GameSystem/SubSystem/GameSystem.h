// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <Delegates/DelegateCombinations.h>
#include <GameSystem.generated.h>

class AAnomaly_Generator;
class AAnomaly_Event;
class AAnomaly_Object_Base;

#pragma region Declare

UENUM(BlueprintType)
enum class EAnomalyVerdictMode : uint8
{
	SolvedOnly,
	Both_AND,
	Normal
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameClearEvent);

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

#pragma region AnomalyState

private:
	bool bIsAnomalySolved = false;
	bool bIsElevatorNormal = false;

public:
	bool GetIsAnomalySolved() const { return bIsAnomalySolved; }
	void SetIsAnomalySolved(bool bIsSolved) { bIsAnomalySolved = bIsSolved; };
	bool GetIsElevatorNormal() const { return bIsElevatorNormal; }
	void SetIsElevatorNormal(bool bIsNormal) { bIsElevatorNormal = bIsNormal; };

#pragma endregion

#pragma region Floor

public:
	uint8 Floor = 9;

private:
	void ResetFloor() { Floor = 9; };
	void SubFloor();
	void AddFloor();

#pragma endregion

#pragma region Verdict

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Verdict")
	EAnomalyVerdictMode VerdictMode;

	bool bPassed = false;

public:
	void SetVerdictMode(EAnomalyVerdictMode ENewMode) { VerdictMode = ENewMode; };
	bool ComputeVerdict(bool bIsSolved, bool bIsCorrectElevator) const;
	void ApplyVerdict();
	void TryInteractSolveVerdict();

#pragma endregion

#pragma region Anomaly

public:
	UPROPERTY(BlueprintReadWrite, Category = "Anomaly|Count")
	uint8 AnomalyCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Count")
	uint8 CurrentAnomalyID = -1;

	UPROPERTY(EditAnywhere, Category = "Anomaly")
	TObjectPtr<class AAnomaly_Event> CurrentAnomaly;

#pragma endregion

#pragma region Pool

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly|Pool")
	uint8 ActIndex = 0;

public:
	void InitializePool();

#pragma endregion

#pragma region Clear

public:
	UFUNCTION()
	void GameClear();

public:
	bool bIsClear = false;
	bool bIsAlreadyClear = false;
	FGameClearEvent GameClearEvent;

#pragma endregion

#pragma region AnomalyChooseKeyVal

public:
	UPROPERTY(BlueprintReadWrite, Category = "AnomalyData")
	int32 GlobalSelectedKeyIndex = 0;

#pragma endregion
};