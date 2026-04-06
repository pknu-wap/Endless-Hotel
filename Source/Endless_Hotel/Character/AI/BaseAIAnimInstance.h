// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAIAnimInstance.generated.h"


UENUM(BlueprintType)
enum class EAIAnimState : uint8
{
	Idle		UMETA(DisplayName = "Idle"),
	Running		UMETA(DisplayName = "Running"),
	Attacking	UMETA(DisplayName = "Attacking")
};

UCLASS()
class ENDLESS_HOTEL_API UBaseAIAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAIAnimState State;

	UFUNCTION(BlueprintCallable)
	void OnStateAnimationEnds();
};
