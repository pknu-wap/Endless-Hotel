// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
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
	UFUNCTION()
	bool GetIsAnomalySolved() const { return bIsAnomalySolved; }

	UFUNCTION()
	void SetIsAnomalySolved(bool bIsSolved) { bIsAnomalySolved = bIsSolved; };

	UFUNCTION()
	bool GetIsElevatorNormal() const { return bIsElevatorNormal; }

	UFUNCTION()
	void SetIsElevatorNormal(bool bIsNormal) { bIsElevatorNormal = bIsNormal; };

#pragma endregion

#pragma region Floor

private:
	uint8 Floor = 9;

private:
	UFUNCTION()
	void ResetFloor() { Floor = 9; };

	UFUNCTION()
	void SubFloor();

	UFUNCTION()
	void AddFloor();

#pragma endregion

#pragma region Verdict

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Verdict")
	EAnomalyVerdictMode VerdictMode;

public:
	UFUNCTION()
	void SetVerdictMode(EAnomalyVerdictMode ENewMode) { VerdictMode = ENewMode; };

	UFUNCTION()
	bool ComputeVerdict(bool bIsSolved, bool bIsCorrectElevator) const;

	UFUNCTION()
	void ApplyVerdict();

#pragma endregion

#pragma region AnomalyCount

public:
	UPROPERTY(BlueprintReadWrite, Category = "Anomaly|Count")
	uint8 AnomalyCount = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Anomaly|Count")
	TArray<uint8> AnomalyHistory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Count")
	uint8 CurrentAnomalyID = -1;

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
	UFUNCTION()
	void InitializePool();

#pragma endregion

#pragma region AnomalyDataBase

protected:
	UPROPERTY()
	TObjectPtr<class UDataTable> DataTable_Anomaly;

public:
	void GetAnomalyData();

	TSubclassOf<AAnomaly_Object_Base> GetObjectByID(uint8 ObjectID);

#pragma endregion
};