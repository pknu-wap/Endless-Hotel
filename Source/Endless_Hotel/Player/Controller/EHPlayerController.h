// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EHPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class UEnhancedInputComponent;
class USpringArmComponent;
class ACharacter;
struct FInputActionValue;

UCLASS()
class ENDLESS_HOTEL_API AEHPlayerController : public APlayerController
{
	GENERATED_BODY()

#pragma region Base
public:
	AEHPlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
#pragma endregion

#pragma region Input
protected:
	virtual void SetupInputComponent() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> IMC_Default;

	// Move - 2D Vector로 통합
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Move;

	// Look - 2D Vector로 통합
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Look;

	// Run
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Run;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float WalkSpeed = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float RunSpeed = 700.0f;

	// Interact 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Interact;

	bool bCanInteract;
	float TraceDistance;

	UPROPERTY()
	AActor* CurrentInteractActor;

	// Crouch
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Crouch;

	// FaceCover
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_FaceCover;

	// Look Sensitivity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float LookSensitivity = 0.3f;

	// Input Callbacks
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void OnRunStarted();
	void OnRunCompleted();
	void OnCrouchStarted();
	void OnCrouchCompleted();
	void OnFaceCoverTriggered();
	void OnInteract(const FInputActionValue& Value);

	/** Tick 내 상호작용 탐색 */
	void CheckForInteractables();

#pragma endregion

#pragma region Components
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCameraComponent;

	// Helper function to get camera
	UCameraComponent* GetPlayerCamera() const;
#pragma endregion

#pragma region Widget
protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUI_PopUp_Base> UI_Escape;
#pragma endregion

#pragma region State
protected:
	bool bIsFaceCovering = false;
	bool bIsCameraFixed = false;
	bool bCanMove = true;
	bool bIsRunning = false;
	bool bIsCrouching = false;
#pragma endregion
};