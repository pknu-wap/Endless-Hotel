// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Character/AI/BaseAIAnimInstance.h"
#include <CoreMinimal.h>
#include <ElevatorGhostAnimInstance.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UElevatorGhostAnimInstance : public UBaseAIAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	bool bIsAttacking;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	bool bIsMoving;
};