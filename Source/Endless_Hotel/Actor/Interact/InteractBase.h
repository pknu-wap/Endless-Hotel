// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include "Interface/Interact/Interactable.h"
#include "Component/Interact/InteractComponent.h"
#include <CoreMinimal.h>
#include <InteractBase.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AInteractBase : public AEHActor, public IInteractable
{
	GENERATED_BODY()
	
#pragma region Base

public:
	AInteractBase(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Mesh

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> Object;

#pragma endregion

#pragma region Interact

public:
	virtual void Interact_Implementation(AEHCharacter* Interacter) override {}

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UWidgetComponent> Component_Widget;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UInteractComponent> Component_Interact;

#pragma endregion

};