// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include "Interact/Interactable.h"
#include <CoreMinimal.h>
#include <Anomaly_Object_Base.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Base : public AEHActor, public IInteractable
{
	GENERATED_BODY()

#pragma region Base

public:
	AAnomaly_Object_Base(const FObjectInitializer& ObjectInitializer);

#pragma endregion


#pragma region Anomaly

public:
	uint8 AnomalyID;

#pragma endregion

#pragma region Object

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Object;

#pragma endregion

#pragma region Interact

public:
	virtual void Interacted_Implementation() override;
	virtual void ShowInteractWidget_Implementation(bool bIsShow) override;
	virtual void SetInteraction() {};

protected:
	virtual void StartInteractaction();

public:
	FText DescriptionText;

	UPROPERTY()
	TObjectPtr<class UUI_Interact> UI_Interact;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UWidgetComponent> WC;

	UPROPERTY()
	TObjectPtr<class ULookAtComponent> LAC;

	TFunction<void()> InteractAction;

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