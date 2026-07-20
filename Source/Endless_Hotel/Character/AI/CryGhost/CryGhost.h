// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Character/AI/BaseAI.h"
#include <CoreMinimal.h>
#include <CryGhost.generated.h>

#pragma region Enum

UENUM(BlueprintType)
enum class ECryGhostState : uint8
{
	Cry			= 0		UMETA(DisplayName = "Cry"),
	Stand		= 1		UMETA(DisplayName = "Stand"),
	JumpScare	= 2		UMETA(DisplayName = "JumpScare"),
	End			= 3		UMETA(DisplayName = "End")
};

FORCEINLINE ECryGhostState& operator++(ECryGhostState& Value)
{
	uint8 Index = (static_cast<uint8>(Value) + 1) % static_cast<uint8>(ECryGhostState::End);
	Value = static_cast<ECryGhostState>(Index);
	return Value;
}

FORCEINLINE ECryGhostState& operator++(ECryGhostState& Value, int)
{
	ECryGhostState Temp = Value;
	++Value;
	return Temp;
}

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API ACryGhost : public ABaseAI
{
	GENERATED_BODY()
	
#pragma region Base

public:
	ACryGhost(const FObjectInitializer& ObjectInitializer);

#pragma endregion

#pragma region State

public:
	void SetCryState();
	void AdvanceCryGhostState();
	const ECryGhostState& GetCurrentState() { return CurrentState; }

private:
	ECryGhostState CurrentState = ECryGhostState::Cry;

#pragma endregion

#pragma region Sound

public:
	UFUNCTION()
	void PlayCrySound();
	void PlayStandSound();
	void PlayJumpScareSound();

private:
	void PlaySound(class USoundWave* SoundWave);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAudioComponent> AudioComponent;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> SW_Cry;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> SW_Stand;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<class USoundWave> SW_JumpScare;

#pragma endregion

#pragma region Targeting

private:
	void AdjustGhostRotation();

private:
	FTimerHandle TargetingHandle;

	UPROPERTY()
	TWeakObjectPtr<ACharacter> TargetPlayer;

#pragma endregion

#pragma region Run

public:
	void RunCryGhost();
	void StopCryGhost();

protected:
	UPROPERTY(EditAnywhere, Category = "Run")
	TObjectPtr<UAnimMontage> AM_Run;

#pragma endregion

};