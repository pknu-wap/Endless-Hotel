// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Anomaly_Base.generated.h"

#pragma region Declare

// Forward Declaration
class UAnomalyProgressSubSystem;

// ================= Verdict Mode =================
UENUM(BlueprintType)
enum class EAnomalyVerdictMode : uint8
{
	CorrectElevatorOnly UMETA(DisplayName = "Correct Elevator Only"),
	SolvedOnly          UMETA(DisplayName = "Solved Only"),
	Both_AND            UMETA(DisplayName = "Both (AND)"),
	Either_OR           UMETA(DisplayName = "Either (OR)")
};

#pragma endregion

UCLASS(Blueprintable, BlueprintType)
class ENDLESS_HOTEL_API AAnomaly_Base : public AActor
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Base(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#pragma endregion

#pragma region Params
public:
	// ===== Verdict Inputs (BP에서 읽고/쓰기) =====
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Verdict")
	bool bIsCorrectElevator = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Verdict")
	bool bIsSolved = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Verdict")
	EAnomalyVerdictMode VerdictMode = EAnomalyVerdictMode::Both_AND;

	// ===== Identity =====
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly|ID")
	int32 AnomalyID = -1;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Anomaly|State")
	bool bIsActive = false;

#pragma endregion
#pragma region Verdicts

	UFUNCTION(BlueprintCallable, Category = "Anomaly|Verdict")
	void SetSolved(bool bNewSolved);

	UFUNCTION(BlueprintCallable, Category = "Anomaly|Verdict")
	void SetCorrectElevator(bool bNewCorrect);

	UFUNCTION(BlueprintCallable, Category = "Anomaly|Verdict")
	bool SubmitVerdictWith(bool bSolved, bool bCorrectElevator);

	UFUNCTION(BlueprintCallable, Category = "Anomaly|Verdict")
	void SubmitVerdict();

#pragma endregion

#pragma region Activity

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Anomaly|Lifecycle")
	void ActivateAnomaly();
	virtual void ActivateAnomaly_Implementation();

#pragma endregion

#pragma region Inner Verdicts

private:
	bool EvaluateOutcome() const;
	void FinalizeAnomaly(bool bPassed);
	void MarkSolved();
	void MarkFailed();
	void PushVerdict();

#pragma endregion

};
