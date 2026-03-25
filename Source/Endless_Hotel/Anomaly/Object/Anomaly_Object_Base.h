// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Actor/Interact/InteractBase.h"
#include "Component/Interact/InteractComponent.h"
#include "Type/Anomaly/Type_AnomalyName.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Base.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Base : public AInteractBase
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Anomaly

public:
	void SetSolvedFalse() { bSolved = false; }
	void SetAnomalyName() { AnomalyName = static_cast<EAnomalyName>(AnomalyID); }

public:
	uint8 AnomalyID;

	UPROPERTY(EditAnywhere, Category = "Anomaly")
	TArray<EAnomalyName> ExecuteAnomalies;

protected:
	EAnomalyName AnomalyName;

#pragma endregion

#pragma region Interact

public:
	UPROPERTY(EditAnyWhere)
	EInteractType CorrectInteractType = EInteractType::None;

public:
	virtual void Interact_Implementation(AEHCharacter* Interacter) override;

#pragma endregion

#pragma region Verdict

public:
	bool bSolved = true;

#pragma endregion

#pragma region Restore

public:
	void StartRestoring(float Duration = 2.5f);
	void SaveOriginalTransform();
	
	bool bIsRestored = false;

private:
	void RestoreTick();
	void FinishRestoring();

	float RestoreDuration = 2.5f;
	float RestoreCurrentTime = 0.f;

public:
	FTransform OriginalTransform;
	FTransform StartTransform;
	FTimerHandle RestoreHandle;

#pragma endregion

};