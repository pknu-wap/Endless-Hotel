// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Actor/EHActor.h"
#include <CoreMinimal.h>
#include <Elevator_Button.generated.h>

#pragma region Declare

class AElevator;

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API AElevator_Button : public AEHActor
{
	GENERATED_BODY()

#pragma region Base

public:
	AElevator_Button(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Elevator

protected:
	UPROPERTY(EditAnywhere, Category = "Elevator")
	TObjectPtr<AElevator> OwnerElevator;

#pragma endregion

#pragma region Button

public:
	UPROPERTY(EditAnywhere, Category = "Button")
	TObjectPtr<UStaticMeshComponent> Pannel;

	UPROPERTY(EditAnywhere, Category = "Button")
	TObjectPtr<UStaticMeshComponent> Up_Button;

	UPROPERTY(EditAnywhere, Category = "Button")
	TObjectPtr<UStaticMeshComponent> Up_ButtonRing;

	UPROPERTY(EditAnywhere, Category = "Button")
	TObjectPtr<UStaticMeshComponent> Down_Button;

	UPROPERTY(EditAnywhere, Category = "Button")
	TObjectPtr<UStaticMeshComponent> Down_ButtonRing;

#pragma endregion

#pragma region Interact

public:
	void InteractElevator();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UWidgetComponent> Component_Widget;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UInteractComponent> Component_Interact;

protected: 
	void MoveToButtonPlayer();

	UFUNCTION()
	void OnMoveCompleted();

	UPROPERTY(EditAnywhere, Category = "Elevator")
	float PlayerToElevatorDistance = 50.0f;

#pragma endregion

};