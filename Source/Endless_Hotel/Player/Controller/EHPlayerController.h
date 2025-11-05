// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

	void EscapeStarted(const struct FInputActionValue& InputValue);

protected:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> IMC_Default;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> IA_ESC;

	//RUN
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Run;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float WalkSpeed = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float RunSpeed = 700.0f;


	//Interact 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Interact;
	bool bCanInteract;
	float TraceDistance;
	UPROPERTY()
	AActor* CurrentInteractActor;

	//FaceCover
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_FaceCover;
	void FaceCover_Triggered();

	/** Tick 내 상호작용 탐색 */
	void CheckForInteractables();

	/** 상호작용 키 눌렀을 때 */
	void OnInteract(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_MoveForward;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_MoveRight;

	// Input Actions - Look
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_LookForward;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_LookRight;

	//Crouch
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* IA_Crouch;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCameraComponent;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;

	// Look Sensitivity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float LookSensitivity = 0.3f;

	// Input Callbacks
	void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void LookForward(const FInputActionValue& Value);
	void LookRight(const FInputActionValue& Value);
#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUI_PopUp_Base> UI_Escape;

	// Helper function to get camera
	UCameraComponent* GetPlayerCamera() const;

	bool bIsFaceCovering = false;
	bool bIsCameraFixed = false;
	bool bCanMove = true;

	bool bIsRunning = false;

	void OnRunTriggered();
	void OnRunCompleted();

	bool bIsCrouching = false;
	void Crouch_Triggered();
	void Crouch_Completed();
#pragma endregion

};