// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Actor/Interact/InteractBase.h"
#include "Type/Anomaly/Type_AnomalyID.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Base.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Base : public AInteractBase
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#pragma endregion

#pragma region Reset

public:
	UFUNCTION()
	virtual void Reset();

#pragma endregion

#pragma region Anomaly

public:
	void SetSolvedFalse() { bSolved = false; }
	void SetAnomalyName(EAnomalyID AnomalyID) { AnomalyName = AnomalyID; }

public:
	UPROPERTY(EditAnywhere, Category = "Anomaly")
	TArray<EAnomalyID> ExecuteAnomalies;

	UPROPERTY(EditAnywhere, Category = "Anomaly|Object")
	bool bIsEightExitObject = false;

protected:
	EAnomalyID AnomalyName;

#pragma endregion

#pragma region Interact

public:
	TArray<EInteractType> CorrectInteractTypes;
	bool bIsOrderedInteractTypes = false;

public:
	virtual void Interact_Implementation(AEHCharacter* Interacter) override;

#pragma endregion

#pragma region Verdict

public:
	bool bSolved = true;

#pragma endregion

#pragma region Floating

public:
	void StartFloating();

#pragma endregion

#pragma region Restore

public:
	void StartRestoring(float Duration = 2.5f);

public:
	FTransform OriginalTransform;

#pragma endregion

};