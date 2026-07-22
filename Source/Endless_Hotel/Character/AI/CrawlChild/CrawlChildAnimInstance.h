// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Character/AI/BaseAIAnimInstance.h"
#include <CoreMinimal.h>
#include <CrawlChildAnimInstance.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UCrawlChildAnimInstance : public UBaseAIAnimInstance
{
	GENERATED_BODY()

#pragma region Settings

public:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	bool bIsCrawling = false;

#pragma endregion

};