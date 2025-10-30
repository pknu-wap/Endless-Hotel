// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AnomalyProgressSubSystem.generated.h"

class AAnomaly_Generator;
class AAnomaly_Base;

#pragma region Declare

UENUM(BlueprintType)
enum class EAnomalyVerdictMode : uint8
{
	AnomalyElevatorOnly,
	SolvedOnly,
	Both_AND,
	Either_OR
};

USTRUCT(BlueprintType)
struct FAnomalyEntry
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<AAnomaly_Base> Class;

	UPROPERTY()
	uint8 AnomalyID;
};

#pragma endregion


UCLASS()
class ENDLESS_HOTEL_API UAnomalyProgressSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

#pragma region Base

public:
	UAnomalyProgressSubSystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

#pragma endregion

#pragma region AnomalyState

private:
	bool bIsAnomalySolved = false;
	bool bIsElevatorNormal = false;

public:
	UFUNCTION(BlueprintCallable, Category = "Anomaly|State")
	bool GetIsAnomalySolved() const { return bIsAnomalySolved; }

	UFUNCTION(BlueprintCallable, Category = "Anomaly|State")
	void SetIsAnomalySolved(bool bNewValue) { bIsAnomalySolved = bNewValue; };

	UFUNCTION(BlueprintCallable, Category = "Anomaly|State")
	bool GetIsElevatorNormal() const { return bIsElevatorNormal; }

	UFUNCTION(BlueprintCallable, Category = "Anomaly|State")
	void SetIsElevatorNormal(bool bNewValue) { bIsElevatorNormal = bNewValue; };

#pragma endregion

#pragma region Floor

private:
	uint8 Floor = 9;

private:
	UFUNCTION(BlueprintCallable, Category = "Anomaly|Floor")
	void SetFloor();

	UFUNCTION(BlueprintCallable, Category = "Anomaly|Floor")
	void SubFloor();

	UFUNCTION(BlueprintCallable, Category = "Anomaly|Floor")
	void AddFloor();

#pragma endregion

#pragma region AnomalyGenerate

public:
	UFUNCTION(BlueprintCallable, Category = "Anomaly|Generate")
	void AnomalySpawn();

#pragma endregion

#pragma region Verdict

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Verdict")
	EAnomalyVerdictMode VerdictMode;

	UFUNCTION(BlueprintCallable, Category = "Anomaly|Verdict")
	void SetVerdictMode(EAnomalyVerdictMode NewMode = EAnomalyVerdictMode::AnomalyElevatorOnly) { VerdictMode = NewMode; };

	UFUNCTION(BlueprintCallable, Category = "Anomaly|Verdict")
	bool ComputeVerdict(bool bSolved, bool bCorrectElevator) const;

	UFUNCTION(BlueprintCallable, Category = "Anomaly|Verdict")
	void ApplyVerdict();

#pragma endregion

#pragma region AnomalyCount

public:
	UPROPERTY(BlueprintReadWrite, Category = "Anomaly|Count")
	int32 AnomalyCount = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Anomaly|Count")
	TArray<int32> AnomalyHistory;

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
	int32 ActIndex = 0;

public:
	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	void InitializePool(bool bShuffle = true);

	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	void ResetSequence(bool bShuffle = true);

#pragma endregion

#pragma region AnomalyDataBase

protected:
	UPROPERTY()
	TObjectPtr<class UDataTable> DataTable_Anomaly;

public:
	void GetAnomalyData();

public:
	uint8 GetAnomalyDataByID(uint8 AnomalyID);

#pragma endregion

};