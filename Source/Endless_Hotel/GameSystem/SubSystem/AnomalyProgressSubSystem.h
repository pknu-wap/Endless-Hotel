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
	bool GetIsAnomalySolved() const { return bIsAnomalySolved; }

<<<<<<< HEAD
	void SetIsAnomalySolved(bool bIsSolved) { bIsAnomalySolved = bIsSolved; };
=======
	UFUNCTION(BlueprintCallable, Category = "Anomaly|State")
	void SetIsAnomalySolved(bool bNewValue) { bIsAnomalySolved = bNewValue; };
>>>>>>> parent of 0cbff4e (Merge remote-tracking branch 'origin/Develop' into origin/Feature/Anomaly)

	bool GetIsElevatorNormal() const { return bIsElevatorNormal; }

<<<<<<< HEAD
	void SetIsElevatorNormal(bool bIsNormal) { bIsElevatorNormal = bIsNormal; };
=======
	UFUNCTION(BlueprintCallable, Category = "Anomaly|State")
	void SetIsElevatorNormal(bool bNewValue) { bIsElevatorNormal = bNewValue; };
>>>>>>> parent of 0cbff4e (Merge remote-tracking branch 'origin/Develop' into origin/Feature/Anomaly)

#pragma endregion

#pragma region Floor

private:
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

<<<<<<< HEAD
public:
	void SetVerdictMode(EAnomalyVerdictMode ENewMode) { VerdictMode = ENewMode; };

	bool ComputeVerdict(bool bIsSolved, bool bIsCorrectElevator) const;
=======
	UFUNCTION(BlueprintCallable, Category = "Anomaly|Verdict")
	void SetVerdictMode(EAnomalyVerdictMode NewMode) { VerdictMode = NewMode; };

	UFUNCTION(BlueprintCallable, Category = "Anomaly|Verdict")
	bool ComputeVerdict(bool bSolved, bool bCorrectElevator) const;
>>>>>>> parent of 0cbff4e (Merge remote-tracking branch 'origin/Develop' into origin/Feature/Anomaly)

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
<<<<<<< HEAD
	void InitializePool();
=======
	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	void InitializePool(bool bShuffle = true);

	UFUNCTION(BlueprintCallable, Category = "Anomaly")
	void ResetSequence(bool bShuffle = true);
>>>>>>> parent of 0cbff4e (Merge remote-tracking branch 'origin/Develop' into origin/Feature/Anomaly)

#pragma endregion

#pragma region AnomalyDataBase

protected:
	UPROPERTY()
	TObjectPtr<class UDataTable> DataTable_Anomaly;

public:
	void GetAnomalyData();

	TSubclassOf<AAnomaly_Object_Base> GetObjectByID(uint8 ObjectID);

	TSubclassOf<AAnomaly_Object_Base> GetObjectByName(FString ObjectName);

	TSubclassOf<AAnomaly_Object_Base> GetObjectByRowIndex(uint8 RowIndex);

#pragma endregion

};