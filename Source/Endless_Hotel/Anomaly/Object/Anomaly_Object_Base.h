// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include "Component/Interact/InteractComponent.h"
#include "Type/Anomaly/Type_AnomalyName.h"
#include "Interface/Interact/Interactable.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Base.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Base : public AEHActor, public IInteractable
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_Base(const FObjectInitializer& ObjectInitializer);

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

#pragma region Object

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Object;

#pragma endregion

#pragma region Interact

public:
	virtual void Interact_Implementation(AEHCharacter* Interacter) override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UWidgetComponent> Component_Widget;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UInteractComponent> Component_Interact;

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