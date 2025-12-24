// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Actor/EHActor.h"
#include "Interact/InteractableObject.h"
#include "Elevator_Button.generated.h"

#pragma region Declare

class AElevator;

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API AElevator_Button : public AEHActor, public IInteractableObject
{
	GENERATED_BODY()

#pragma region Base

protected:
	AElevator_Button(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region Elevator

protected:
	UPROPERTY(VisibleAnywhere, Category = "Elevator")
	TObjectPtr<AElevator> OwnerElevator;

public:
	void SetOwnerElevator(AElevator* InElevator) { OwnerElevator = InElevator; }

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
	virtual void Interacted_Implementation() override;

	virtual FText GetDescriptionText_Implementation() override;

#pragma endregion

};