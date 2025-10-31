// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Anomaly_Base.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ENDLESS_HOTEL_API AAnomaly_Base : public AActor
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Base(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#pragma endregion

#pragma region ObjectLinker

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly|Linker")
	TArray<AActor*> LinkedObjects;

#pragma endregion

#pragma region Params
public:
	// Verdict Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Verdict")
	bool bIsCorrectElevator = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Verdict")
	bool bIsSolved = false;

	// ID
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anomaly|ID")
	uint8 AnomalyID = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anomaly|ID")
	uint8 ObjectID = -1;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Anomaly|State")
	bool bIsActive = false;

#pragma endregion

#pragma region Verdicts

	UFUNCTION(BlueprintCallable, Category = "Anomaly|Verdict")
	void SetSolved(bool bNewSolved);

	UFUNCTION(BlueprintCallable, Category = "Anomaly|Verdict")
	void SetCorrectElevator(bool bNewCorrect) { bIsCorrectElevator = bNewCorrect; };

protected:
	UFUNCTION(BlueprintCallable, Category = "Anomaly|VerdictMode")
	void SetVerdictMode(EAnomalyVerdictMode NewMode);

#pragma endregion

#pragma region Activity

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Anomaly|Lifecycle")
	void ActivateAnomaly(uint8 Anomaly_ID);
	virtual void ActivateAnomaly_Implementation(uint8 Anomaly_ID);

#pragma endregion

#pragma region Inner Verdicts

private:
	void FinalizeAnomaly(bool bPassed);
	void MarkSolved();
	void MarkFailed();

#pragma endregion

};
