// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <GameFramework/PlayerController.h>
#include <EHPlayerController.generated.h>

class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class UEnhancedInputComponent;
class USpringArmComponent;
class ACharacter;
class AEHPlayer;
class USpotLightComponent;
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

protected:
	UPROPERTY()
	TWeakObjectPtr<class AEHPlayer> EHPlayer;

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

	// Interact 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_Interact;

	// Interact 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_ChangeInteract;

	// Crouch
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_Crouch;

	// FaceCover
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_FaceCover;
	bool bIsFaceCoverTransitioning = false;

	//Light
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> IA_Light;

	//ESC
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> IA_ESC;

#pragma endregion

#pragma region Move

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float WalkSpeed = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float RunSpeed = 600.0f;

protected:
	void Move(const FInputActionValue& Value);

#pragma endregion

#pragma region Look

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float LookSensitivity = 1.1f;

public:
	void SetLookSensitivity(float Value) { LookSensitivity = 0.2f + Value * 1.8f; }
	void Look(const FInputActionValue& Value);

#pragma endregion

#pragma region Interact

protected:
	UPROPERTY()
	TWeakObjectPtr<class UInteractComponent> CachedInteractComp;

protected:
	const float TraceDistance = 100.f;

protected:
	void CheckForInteractables();
	void OnInteract(const FInputActionValue& Value);
	void ChangeInteract(const FInputActionValue& Value);

#pragma endregion

#pragma region Widget

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUI_Base> UI_Escape;

protected:
	void EscapeStarted(const struct FInputActionValue& InputValue);

#pragma endregion

#pragma region Components

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UCameraComponent> PlayerCameraComponent;

	// Helper function to get camera
	UCameraComponent* GetPlayerCamera() const;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class USpotLightComponent> FlashLight;

#pragma endregion

#pragma region State

public:
	bool bIsFaceCovering = false;
	bool bIsCameraFixed = false;
	bool bCanMove = true;
	bool bCanRun = true;
	bool bCanCrouch = true;
	bool bCanFaceCover = true;
	bool bIsRunning = false;
	bool bIsCrouching = false;
	bool bIsButtonPressing = false;

public:
	bool GetIsRunning() const { return bIsRunning; }
	bool GetIsCrouching() const { return bIsCrouching; }
	bool GetIsFaceCovering() const { return bIsFaceCovering; }
	bool GetIsButtonPressingCovering() const { return bIsButtonPressing; }

#pragma endregion

#pragma region State_Death

public:
	void PlayDeathSequence();
	void RevivePlayer();

public:
	bool bIsPlayerDead = false;
	bool GetIsPlayerDead() const { return bIsPlayerDead; }

#pragma endregion

#pragma region State_Run
	
protected:
	void OnRunStarted();
	void OnRunCompleted();

#pragma endregion

#pragma region State_Crouch

protected:
	void OnCrouchStarted();
	void OnCrouchCompleted();

#pragma endregion

#pragma region State_FaceCover

protected:
	void OnFaceCoverStarted();
	void OnFaceCoverCompleted();

#pragma endregion

#pragma region State_EVButton

public:
	void OnEVButtonPressStarted();
	void OnEVButtonPressCompleted();

#pragma endregion

#pragma region State_HandLight

protected:
	void TurnPlayerHandLight();

#pragma endregion

#pragma region SetInput
	
public:
	void SetPlayerInputAble(bool Able);

#pragma region HeartbeatSound

public:
	void SetHeartbeatSound(AActor* Monster);

	void StopHeartbeatSound();

protected:
	void UpdateHeartbeatSound(float DeltaSeconds);

protected:
	UPROPERTY()
	TObjectPtr<UAudioComponent> CachedHeartbeatComp;

	UPROPERTY(EditAnywhere, Category = "HeartbeatSound")
	TWeakObjectPtr<class AActor> HeartbeatMonster;

	UPROPERTY(EditAnywhere, Category = "HeartbeatSound")
	float MaxDistance = 2000.0f;

	UPROPERTY(EditAnywhere, Category = "HeartbeatSound")
	float MinDistance = 300.0f;

#pragma endregion

#pragma region Key

public:
	void SetKeyMapping(struct FKeySettingInfo Info);

#pragma endregion

};