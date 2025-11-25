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

	// Move
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_Move;

	// Look
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_Look;

	// Run
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_Run;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float WalkSpeed = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float RunSpeed = 600.0f;

	// Interact 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_Interact;

	bool bCanInteract;
	float TraceDistance;

	UPROPERTY()
	TObjectPtr<class AActor> CurrentInteractActor;

	// Crouch
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_Crouch;

	// FaceCover
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_FaceCover;
	bool bIsFaceCoverTransitioning = false;

	//ESC
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> IA_ESC;

	// Look Sensitivity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float LookSensitivity = 0.3f;

	// Input Callbacks
	void EscapeStarted(const struct FInputActionValue& InputValue);
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void OnRunStarted();
	void OnRunCompleted();
	void OnCrouchStarted();
	void OnCrouchCompleted();
	void OnFaceCoverStarted();
	void OnFaceCoverCompleted();
	void OnInteract(const FInputActionValue& Value);

	/** Tick 내 상호작용 탐색 */
	void CheckForInteractables();

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUI_PopUp_Base> UI_Escape;

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

#pragma region State
public:
	bool bIsFaceCovering = false;
	bool bIsCameraFixed = false;
	bool bCanMove = true;
	bool bCanRun = true;
	bool bIsRunning = false;
	bool bIsCrouching = false;

	bool GetIsRunning() const { return bIsRunning; }
	bool GetIsCrouching() const { return bIsCrouching; }
	bool GetIsFaceCovering() const { return bIsFaceCovering; }
#pragma endregion
};