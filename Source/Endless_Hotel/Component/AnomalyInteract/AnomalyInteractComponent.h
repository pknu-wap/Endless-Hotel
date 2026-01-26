// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Component/EHComponent.h"
#include "Interact/Interactable.h"
#include <CoreMinimal.h>
#include <AnomalyInteractComponent.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UAnomalyInteractComponent : public UEHComponent, public IInteractable
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void BeginPlay() override;

public:
	TObjectPtr<class AAnomaly_Object_Base> OwnerObject;

#pragma endregion

#pragma region Interact

public:
	bool bIsAbnormal;

public:
	virtual void SetAnomalyInteract();

#pragma endregion

};
