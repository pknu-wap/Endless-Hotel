// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Actor/EHActor.h"
#include "Anomaly_Base.generated.h"

#pragma region Declare

class AAnomaly_Object_Base;

#pragma endregion

UCLASS(Blueprintable, BlueprintType)
class ENDLESS_HOTEL_API AAnomaly_Base : public AEHActor
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

#pragma region Anomaly

protected:
	virtual void StartAnomalyAction();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anomaly|ID")
	uint8 AnomalyID = -1;

protected:
	TFunction<void(class AAnomaly_Object_Base*)> AnomalyAction;

#pragma endregion

#pragma region Verdicts

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Verdict")
	bool bIsCorrectElevator = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anomaly|Verdict")
	bool bIsSolved = false;

protected:
	void SetSolved(bool bNewSolved);

	UFUNCTION()
	void SetCorrectElevator(bool bNewCorrect) { bIsCorrectElevator = bNewCorrect; };

	UFUNCTION()
	void SetVerdictMode(EAnomalyVerdictMode NewMode);

#pragma endregion

#pragma region Activity

public:
	virtual void ActivateAnomaly(uint8 Anomaly_ID) {}
	virtual void DisableAnomaly(uint8 Anomaly_ID) {}

#pragma endregion

#pragma region Inner Verdicts

private:
	void FinalizeAnomaly(bool bPassed);
	void MarkSolved();
	void MarkFailed();

#pragma endregion

#pragma region ForTest

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AAnomaly_Object_Base> ObjectClass;

#pragma endregion

};