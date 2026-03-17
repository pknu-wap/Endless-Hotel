// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include "Interface/Interact/Interactable.h"
#include <CoreMinimal.h>
#include <HotelBlueprint.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AHotelBlueprint : public AEHActor, public IInteractable
{
	GENERATED_BODY()

#pragma region Base

public:
	AHotelBlueprint(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region HotelBlueprint

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> SM_HotelBlueprint;

#pragma endregion

#pragma region Interact

public:
	virtual void Interact_Implementation() override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UWidgetComponent> Component_Widget;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UInteractComponent> Component_Interact;

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<class UUI_Base> UI_HotelBlueprint_Class;

#pragma endregion

};