// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UCameraComponent;

UCLASS()
class ENDLESS_HOTEL_API ACPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ACPlayerController();

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

    // Input Actions - Movement
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_MoveForward;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_MoveRight;

    // Input Actions - Look
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_LookForward;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_LookRight;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputMappingContext* InputMappingContext;

    // Look Sensitivity
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    float LookSensitivity = 0.3f;

    // Input Callbacks
    void MoveForward(const FInputActionValue& Value);
    void MoveRight(const FInputActionValue& Value);
    void LookForward(const FInputActionValue& Value);
    void LookRight(const FInputActionValue& Value);

private:
    // Helper function to get camera
    UCameraComponent* GetPlayerCamera() const;
};
