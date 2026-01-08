// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include "Actor/EHActor.h"
#include "Interact/Interactable.h"
#include "Elevator_Button.generated.h"

#pragma region Declare

class AElevator;

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API AElevator_Button : public AEHActor, public IInteractable
{
	GENERATED_BODY()

#pragma region Base

public:
	AElevator_Button(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

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
	virtual void ShowInteractWidget_Implementation(bool bIsShow) override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UWidgetComponent> WC;

	UPROPERTY()
	TObjectPtr<class UUI_Interact> UI_Interact;

	UPROPERTY()
	TObjectPtr<class ULookAtComponent> LAC;

	UPROPERTY(EditInstanceOnly, Category = "Position")
	FVector2D PlayerLocationButton;

	UPROPERTY(EditInstanceOnly, Category = "Rotation")
	FRotator PlayerRotationButton;

	FVector finalloc;
protected: 
	void MoveToButtonPlayer();

#pragma endregion

};