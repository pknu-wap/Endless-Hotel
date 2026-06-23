// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Character/AI/BaseAIAnimInstance.h"
#include <CoreMinimal.h>
#include <TwinAnimInstance.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UTwinAnimInstance : public UBaseAIAnimInstance
{
	GENERATED_BODY()
	
#pragma region State

public:
	UPROPERTY(BlueprintReadOnly)
	bool bIsMove = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsJumpScare = false;

#pragma endregion

};
