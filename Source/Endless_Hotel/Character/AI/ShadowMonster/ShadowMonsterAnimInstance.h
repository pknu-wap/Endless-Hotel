// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "Character/AI/BaseAIAnimInstance.h"
#include <CoreMinimal.h>
#include <ShadowMonsterAnimInstance.generated.h>

UCLASS()
class ENDLESS_HOTEL_API UShadowMonsterAnimInstance : public UBaseAIAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	bool bMonsterAppear = false;
};