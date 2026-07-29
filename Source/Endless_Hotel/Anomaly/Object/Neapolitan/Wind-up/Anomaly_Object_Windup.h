// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Anomaly/Object/Neapolitan/Doll/Anomaly_Object_Doll.h"
#include <Components/AudioComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Animation/AnimationAsset.h>
#include <CoreMinimal.h>
#include <Anomaly_Object_Windup.generated.h>

UCLASS()
class ENDLESS_HOTEL_API AAnomaly_Object_Windup : public AAnomaly_Object_Doll
{
	GENERATED_BODY()

protected:
	enum class EWindupInteractStep : uint8
	{
		NeedStopSound,
		NeedBurn,
		Finished
	};

#pragma region Base

public:
	AAnomaly_Object_Windup(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

#pragma endregion

#pragma region Set

public:
	void SetWindup();

private:
	FTimerHandle DelayHandle;

#pragma endregion

#pragma region Components

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<USkeletalMeshComponent> SKM_Windup;

#pragma region Sound

protected:
	UPROPERTY()
	TObjectPtr<UAudioComponent> AC_Windup;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundWave> Sound_Windup;

	UPROPERTY(EditAnywhere, Category = "Sound")
	uint8 MaxWindupPlayCount = 5;

	UPROPERTY(EditAnywhere, Category = "Sound")
	float WindupPlayInterval = 3.0f;

	uint8 CurrentWindupPlayCount = 0;

	FTimerHandle WindupPlayHandle;
	
	UPROPERTY(EditAnywhere, Category = "Sound")
	int WrongPlayCount = 5;

	UPROPERTY(EditAnywhere, Category = "Sound")
	float WrongPlayInterval = 0.5f;

	uint8 CurrentWrongPlayCount = 0;

	FTimerHandle WrongPlayHandle;

public:
	void WindupPlay();

	void StopWindup();

	void StartWindupLoop();

	void WindupLoopTick();

	void StartWrongLoop();
	
	void WrongLoopTick();

#pragma endregion

#pragma region Animation

protected:
	UPROPERTY(EditAnywhere, Category = "Animation")
	TObjectPtr<UAnimationAsset> WindupAnimation;

	void PlayWindupAnimationOnce();

#pragma endregion

#pragma region Burn

private:
	void SetupWindupBurnTargets();
	void StartWindupBurning();
	void WindupBurnTick();

private:
	UPROPERTY()
	TArray<TObjectPtr<class UMaterialInstanceDynamic>> MID_WindupBurn;

	FTimerHandle WindupBurnHandle;

	float WindupBurnCurrentTime = 0.f;

#pragma endregion

#pragma region Interact

public:
	virtual void Interact_Implementation(class AEHCharacter* Interacter) override;

	EWindupInteractStep CurrentInteractStep = EWindupInteractStep::NeedStopSound;

#pragma endregion
};