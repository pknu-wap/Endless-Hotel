// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"


UENUM(BlueprintType)
enum class EMonsterAnimState : uint8
{
	Locomotion		UMETA(DisplayName = "Chasing"),
	Attacking	UMETA(DisplayName = "Attacking")
};

UCLASS()
class ENDLESS_HOTEL_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMonsterAnimState State;

	UFUNCTION(BlueprintCallable)
	void OnStateAnimationEnds();
};
