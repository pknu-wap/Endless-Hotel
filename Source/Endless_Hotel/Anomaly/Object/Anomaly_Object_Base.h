// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include "Component/Interact/InteractComponent.h"
#include "Type/Anomaly/Type_AnomalyName.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Base.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Base : public AEHActor
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
	uint8 AnomalyID;

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
	virtual void SetInteraction() { AnomalyName = static_cast<EAnomalyName>(AnomalyID); }

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UWidgetComponent> Component_Widget;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UInteractComponent> Component_Interact;

#pragma endregion

#pragma region Restore

protected:
	void RestoreObjectTransform();

protected:
	FTransform OriginalTransform;

	FTimerHandle RestoreHandle;

	float CurrentTime = 0.f;

#pragma endregion

};