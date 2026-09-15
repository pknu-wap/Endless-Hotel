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

#pragma endregion

#pragma region Reset

public:
	virtual void Reset() override;

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
	UPROPERTY(EditAnywhere, Category = "Sound")
	uint8 MaxWindupPlayCount = 5;

	UPROPERTY(EditAnywhere, Category = "Sound")
	float WindupPlayInterval = 3.0f;

	uint8 CurrentWindupPlayCount = 0;

	FTimerHandle WindupPlayHandle;

public:
	void WindupPlay();
	void StopWindup();

	void StartWindupLoop();
	void WindupLoopTick();

	void StartWrongLoop();

#pragma endregion

#pragma region Animation

protected:
	UPROPERTY(EditAnywhere, Category = "Animation")
	TObjectPtr<UAnimationAsset> WindupAnimation;

	UPROPERTY(EditAnywhere, Category = "Animation|Wrong")
	TObjectPtr<UAnimSequenceBase> WrongWindupAnimation;

	UPROPERTY(EditAnywhere, Category = "Animation|Wrong")
	int WrongPlayCount = 8;

	void PlayWindupAnimation();
	void PlayWrongMontage();

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
	virtual void Interact(class AEHCharacter* Interacter) override;

	EWindupInteractStep CurrentInteractStep = EWindupInteractStep::NeedStopSound;

#pragma endregion
};