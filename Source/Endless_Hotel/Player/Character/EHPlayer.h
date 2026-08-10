// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Character/EHCharacter.h"
#include "Type/Player/Type_Death.h"
#include "Type/Save/Type_Save.h"
#include <CoreMinimal.h>
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

#pragma region Component

public:
	class UCameraComponent* GetCamera() { return Camera; }

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UPointLightComponent> Lighter;

#pragma endregion

#pragma region Movement

#define WALK_SPEED 300.f
#define RUN_SPEED 600.f

public:
	void SetWalkSpeed(float Value);

#pragma endregion

#pragma region Spawn

private:
	void RespawnPlayer();

private:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TMap<EGameProgression, FTransform> SpawnTransform;

#pragma endregion

#pragma region Die & Revive

private:
	void DiePlayer(const EDeathReason& DeathReason);
	void RevivePlayer();

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDie, const EDeathReason&);
	FOnDie OnDie;

	DECLARE_MULTICAST_DELEGATE(FOnRevive)
	FOnRevive OnRevive;

	// 삭제 예정 (현재 다른 코드들 때문에 임시로 남김)
	bool bIsDead = false;

private:
	UPROPERTY(EditAnywhere, Category = "Die")
	TMap<EDeathReason, TObjectPtr<UAnimMontage>> DieMontage;

#pragma endregion

#pragma region Interact

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FCanInteract, bool);
	FCanInteract CanInteract;

#pragma endregion

#pragma region Crouch

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCrouched, bool);
	FOnCrouched OnCrouched;

#pragma endregion

#pragma region Sound

public:
	void PlayElevatorSound(bool bIsPlay);

public:
	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class UAudioComponent> HeartbeatAudioComponent;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundBase> HeartbeatSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class UAudioComponent> ElevatorMoveAudioComponent;

#pragma endregion

};