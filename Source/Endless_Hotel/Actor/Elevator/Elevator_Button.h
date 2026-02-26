#pragma once

#include "Actor/EHActor.h"
#include <CoreMinimal.h>
#include <Elevator_Button.generated.h>

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnElevatorButtonPressed);

UCLASS()
class ENDLESS_HOTEL_API AElevator_Button : public AEHActor
{
    GENERATED_BODY()

#pragma region Base

public:
    AElevator_Button(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnElevatorButtonPressed OnButtonPressed;

protected:
    virtual void BeginPlay() override;
#pragma endregion

#pragma region Button

public:
    UPROPERTY(VisibleAnywhere, Category = "Button")
    TObjectPtr<UStaticMeshComponent> Pannel;

    UPROPERTY(VisibleAnywhere, Category = "Button")
    TObjectPtr<UStaticMeshComponent> Up_Button;

    UPROPERTY(VisibleAnywhere, Category = "Button")
    TObjectPtr<UStaticMeshComponent> Up_ButtonRing;

    UPROPERTY(VisibleAnywhere, Category = "Button")
    TObjectPtr<UStaticMeshComponent> Down_Button;

    UPROPERTY(VisibleAnywhere, Category = "Button")
    TObjectPtr<UStaticMeshComponent> Down_ButtonRing;

#pragma endregion

#pragma region Interact

public:
    void InteractElevator();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Interact")
    TObjectPtr<class UWidgetComponent> Component_Widget;

    UPROPERTY(VisibleAnywhere, Category = "Interact")
    TObjectPtr<class UInteractComponent> Component_Interact;

    UPROPERTY(EditAnywhere, Category = "Interact")
    float PlayerToElevatorDistance = 50.0f;

    void MoveToButtonPlayer();

    UFUNCTION()
    void OnMoveCompleted();

protected:
    UPROPERTY(EditAnywhere, Category = "Button Animation")
    float ButtonPressDistance = 0.5f;

    UPROPERTY(EditAnywhere, Category = "Button Animation")
    float ButtonPressDuration = 0.7f;

    UPROPERTY(EditAnywhere, Category = "Button Animation")
    float ButtonTimerDuration = 0.7f;

    UPROPERTY(EditAnywhere, Category = "Audio")
    TObjectPtr<USoundBase> ButtonPressSound;

    UFUNCTION()
    void PlayButtonPressAnimation();

    UFUNCTION()
    void RestoreButtonPosition();

    FVector DownButtonDefaultLocation;
    FVector DownButtonRingDefaultLocation;

#pragma endregion
};