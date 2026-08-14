// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Actor/Interact/InteractBase.h"
#include <CoreMinimal.h>
#include <Elevator_Button.generated.h>

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnElevatorButtonPressed, bool, bIsOpeningDoor);

UCLASS()
class ENDLESS_HOTEL_API AElevator_Button : public AInteractBase
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
    TObjectPtr<UStaticMeshComponent> Up_Button;

    UPROPERTY(VisibleAnywhere, Category = "Button")
    TObjectPtr<UStaticMeshComponent> Up_ButtonRing;

    UPROPERTY(VisibleAnywhere, Category = "Button")
    TObjectPtr<UStaticMeshComponent> Down_Button;

    UPROPERTY(VisibleAnywhere, Category = "Button")
    TObjectPtr<UStaticMeshComponent> Down_ButtonRing;

    UPROPERTY(EditAnywhere, Category = "Button|State")
    bool bIsOpeningButton = true;

#pragma endregion

#pragma region Reset

public:
    UFUNCTION()
    void Reset();

#pragma endregion

#pragma region Interact

public:
    virtual void Interact_Implementation(AEHCharacter* Interacter) override;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interact")
    class UArrowComponent* InteractAnchor;

    void CanPressButton(bool bCanPress);

protected:
    UPROPERTY(EditAnywhere, Category = "Interact")
    float PlayerToElevatorDistance = 50.0f;

    UPROPERTY(EditAnywhere, Category = "Interact")
    float PlayerToElevatorSideOffset = 0.0f;

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