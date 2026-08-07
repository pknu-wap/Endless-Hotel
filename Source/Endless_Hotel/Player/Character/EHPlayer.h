// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Character/EHCharacter.h"
#include "Type/Player/Type_Death.h"
#include <CoreMinimal.h>
#include <Delegates/DelegateCombinations.h>
#include <EHPlayer.generated.h>

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

#pragma region Start

public:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	FTransform StartTransform = FTransform(FRotator(0, 180, 0), FVector(-1200, 1100, 680), FVector(0.75f, 0.75f, 0.75f));

public:
	FVector GetStartScale() const { return StartTransform.GetScale3D(); }

#pragma endregion

#pragma region Component

public:
	class UCameraComponent* GetCamera() { return Camera; }
	class USkeletalMeshComponent* GetThirdMesh() { return Third_Mesh; }

protected:
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
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCanInteract, bool, bCanInteract);
	FCanInteract CanInteract;

#pragma endregion

#pragma region Crouch

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCrouchDelegate, bool, bIsCrouch);
	FCrouchDelegate CrouchDelegate;

#pragma endregion

#pragma region Death

protected:
	UFUNCTION()
	void DiePlayer(const EDeathReason& DeathReason);
	void FreezeAnimation();

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDieDelegate, const EDeathReason&, DeathReason);
	FDieDelegate DieDelegate;

	bool bIsDead = false;

protected:
	UPROPERTY(EditAnywhere, Category = "Death")
	TMap<EDeathReason, TObjectPtr<class UAnimMontage>> DeathAnims;

	UPROPERTY(EditAnywhere, Category = "Death")
	TObjectPtr<class USoundWave> SW_Ringing;

private:
	UPROPERTY()
	TObjectPtr<class UAudioComponent> AC;

#pragma endregion

#pragma region Animation

public:
	void PlayAnimation(UAnimMontage* Montage);

#pragma endregion

};