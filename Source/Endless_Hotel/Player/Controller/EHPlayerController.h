// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/Level/Type_Level.h"
#include <CoreMinimal.h>
#include <GameFramework/PlayerController.h>
#include <EHPlayerController.generated.h>

#pragma region Declare

struct FInputActionValue;

#pragma endregion

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

#pragma region Reference

private:
	UPROPERTY()
	TWeakObjectPtr<class AEHPlayer> EHPlayer;

#pragma endregion

#pragma region Input

public:
	void SetPlayerInputAble(bool bAble);

protected:
	virtual void SetupInputComponent() override;
	
protected:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> IMC_Default;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> IA_Move;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> IA_Look;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> IA_Run;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> IA_Interact;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> IA_ChangeInteract;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> IA_Crouch;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> IA_FaceCover;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> IA_Light;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputAction> IA_ESC;

#pragma endregion

#pragma region Move

private:
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

private:
	UFUNCTION()
	void OpenHUDWidget(const EMapDataLayer& DataLayer);
	void EscapeStarted(const struct FInputActionValue& InputValue);

#pragma endregion

#pragma region Components

private:
	UPROPERTY()
	TWeakObjectPtr<class UCameraComponent> PlayerCamera;

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
	bool bIsPlayerDoorOpening = false;
	bool bIsPlayerPushingDoor = false;
	bool bHasFlash = false;

public:
	bool GetIsRunning() const { return bIsRunning; }
	bool GetIsCrouching() const { return bIsCrouching; }
	bool GetIsFaceCovering() const { return bIsFaceCovering; }
	bool GetIsButtonPressingCovering() const { return bIsButtonPressing; }
	bool GetIsPlayerDoorOpening() const { return bIsPlayerDoorOpening; }
	bool GetIsPlayerPushingDoor() const { return bIsPlayerPushingDoor; }

#pragma endregion

#pragma region Die & Revive

private:
	void DiePlayer(const EDeathReason& DeathReason);
	void RevivePlayer();

#pragma endregion

#pragma region State_Run
	
protected:
	void OnRunStarted();
	void OnRunCompleted();

#pragma endregion

#pragma region State_Crouch

public:
	void OnCrouchStarted();
	void OnCrouchCompleted();

#pragma endregion

#pragma region State_FaceCover

protected:
	void OnFaceCoverStarted();
	void OnFaceCoverCompleted();

private:
	bool bIsFaceCoverTransitioning = false;

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

#pragma region State_FirstDoorOpen

public:
	void OnFirstDoorOpenStarted();
	void OnFirstDoorOpenCompleted();

public:
	void OnPushDoorStarted();
	void OnPushDoorCompleted();

#pragma endregion

#pragma region SetInput
	
public:
	void SetPlayerInputAble(bool bAble);

#pragma endregion

#pragma region Key

public:
	void SetKeyMapping(struct FKeySettingInfo NewInfo, FKey OldKey);

protected:
	UPROPERTY()
	TObjectPtr<class UInputMappingContext> IMC_Backup;

#pragma endregion

#pragma region Watching

public:
	bool IsLookingAtActor(AActor* TargetActor, float Distance, bool bUseCrosshairCheck);
	bool IsLookingAtActor(AActor* TargetActor);
	bool IsActorOnScreen(AActor* TargetActor) const;

private:
	AActor* GetLookedAtActor(float Distance) const;

#pragma endregion

};