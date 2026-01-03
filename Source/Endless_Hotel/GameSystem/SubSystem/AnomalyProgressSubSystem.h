// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Subsystems/GameInstanceSubsystem.h>
#include <Delegates/DelegateCombinations.h>
#include "AnomalyProgressSubSystem.generated.h"

class AAnomaly_Generator;
class AAnomaly_Base;
class AAnomaly_Object_Base;

#pragma region Declare

UENUM(BlueprintType)
enum class EAnomalyVerdictMode : uint8
{
	AnomalyElevatorOnly,
	SolvedOnly,
	Both_AND,
	Normal
};

USTRUCT(BlueprintType)
struct FAnomalyEntry
{
	GENERATED_BODY()

	UPROPERTY()
	uint8 AnomalyID;

	UPROPERTY()
	TSubclassOf<AAnomaly_Base> AnomalyClass;

	UPROPERTY()
	TSubclassOf<AAnomaly_Object_Base> ObjectClass;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameClearEvent);

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API UAnomalyProgressSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

#pragma region Base

public:
	UAnomalyProgressSubSystem();

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

	UPROPERTY(BlueprintReadWrite, Category = "Anomaly|Count")
	TArray<uint8> AnomalyHistory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Count")
	uint8 CurrentAnomalyID = -1;

	UPROPERTY(EditAnywhere, Category = "Anomaly")
	TObjectPtr<class AAnomaly_Base> CurrentAnomaly;

#pragma endregion

#pragma region Pool

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly|Pool")
	TArray<FAnomalyEntry> OriginAnomaly;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly|Pool")
	TArray<FAnomalyEntry> ActAnomaly;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly|Pool")
	uint8 ActIndex = 0;

public:
	void InitializePool();

#pragma endregion

#pragma region AnomalyDataBase

protected:
	UPROPERTY()
	TObjectPtr<class UDataTable> DataTable_Anomaly;

private:
	TSet<uint8> LoadedAnomalySet;

public:
	void GetAnomalyData();

	TSubclassOf<AAnomaly_Object_Base> GetObjectByID(uint8 ObjectID);
	TSubclassOf<AAnomaly_Object_Base> GetObjectByName(FString ObjectName);
	TSubclassOf<AAnomaly_Object_Base> GetObjectByRowIndex(uint8 RowIndex);

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

};