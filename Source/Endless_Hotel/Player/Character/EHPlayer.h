// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Character/Character/EHCharacter.h"
#include "Type/Player/Type_Death.h"
#include <CoreMinimal.h>
#include <Delegates/DelegateCombinations.h>
#include <EHPlayer.generated.h>

#pragma region Declare

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCanInteract, bool, bCanInteract);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDieDelegate, const EDeathReason&, DeathReason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCrouchDelegate, bool, bIsCrouch);

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API AEHPlayer : public AEHCharacter
{
	GENERATED_BODY()

#pragma region Base

public:
	AEHPlayer(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
#pragma endregion

#pragma region Component

public:
	class UCameraComponent* GetCamera() { return Camera; }

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UEHCameraComponent> Component_Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<class USkeletalMeshComponent> Third_Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lighter")
	TObjectPtr<class UPointLightComponent> FlashLight;



#pragma endregion

#pragma region Interact

public:
	FCanInteract CanInteract;

#pragma endregion

#pragma region Crouch

public:
	FCrouchDelegate CrouchDelegate;

#pragma endregion

#pragma region Death

protected:
	UFUNCTION()
	void DiePlayer(const EDeathReason& DeathReason);
	void FreezeAnimation();

public:
	FDieDelegate DieDelegate;

	bool bIsDead = false;

protected:
	UPROPERTY(EditAnywhere)
	TMap<EDeathReason, TObjectPtr<class UAnimMontage>> DeathAnims;

#pragma endregion

#pragma region Sound

public:
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class UAudioComponent> HeartbeatAudioComponent;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundBase> HeartbeatSound;

#pragma endregion

};