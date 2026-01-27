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
	virtual void OnConstruction(const FTransform& Transform) override;

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
	void CurrentInteractionUpdate(uint8 InteractionNumber = 0);

public:
	UPROPERTY(EditAnywhere)
	uint8 CurrentInteractIndex = 0;

	UPROPERTY()
	TObjectPtr<class UUI_Interact> UI_Interact;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	TArray<TObjectPtr<class UAnomalyInteractComponent>> InteractComponents;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UWidgetComponent> WC;

	UPROPERTY()
	TObjectPtr<class ULookAtComponent> LAC;

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