// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AnomalyProgressSubSystem.generated.h"

class AAnomaly_Generator;
class AAnomaly_Base_Ex;

#pragma region Declare

UENUM(BlueprintType)
enum class EAnomalyVerdictMode : uint8
{
	CorrectElevatorOnly,
	SolvedOnly,
	Both_AND,
	Either_OR
};

#pragma endregion


UCLASS()
class ENDLESS_HOTEL_API UAnomalyProgressSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

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
	int32 Floor = 9;

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
	EAnomalyVerdictMode VerdictMode = EAnomalyVerdictMode::CorrectElevatorOnly;

	UFUNCTION(BlueprintCallable, Category = "Anomaly|Verdict")
	void SetVerdictMode(EAnomalyVerdictMode NewMode) { VerdictMode = NewMode; };

	UFUNCTION(BlueprintCallable, Category = "Anomaly|Verdict")
	bool ComputeVerdict(bool bSolved, bool bCorrectElevator) const;

	UFUNCTION(BlueprintCallable, Category = "Anomaly|Verdict")
	void ApplyVerdict();

#pragma endregion
};
