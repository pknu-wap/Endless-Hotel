// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include "Anomaly/Object/Anomaly_Object_Base.h"
#include "Interact/InteractableObject.h"
#include "Anomaly_Object_Neapolitan.generated.h"

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Neapolitan : public AAnomaly_Object_Base, public IInteractableObject
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AAnomaly_Object_Neapolitan(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Verdict

public:
	bool bSolved = false;

#pragma endregion

#pragma region Interact

public:
	virtual void Interacted_Implementation() override;
	virtual void ShowInteractWidget_Implementation(bool bIsShow) override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UWidgetComponent> WC;

	UPROPERTY()
	TObjectPtr<class UUI_Interact> UI_Interact;

	UPROPERTY()
	TObjectPtr<class ULookAtComponent> LAC;

#pragma endregion

};
