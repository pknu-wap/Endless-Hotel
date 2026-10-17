// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Character/AI/BaseAIAnimInstance.h"
#include <CoreMinimal.h>
#include <MouseAnimInstance.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UMouseAnimInstance : public UBaseAIAnimInstance
{
	GENERATED_BODY()
	
#pragma region State

public:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	bool bIsRun = true;

#pragma endregion

};