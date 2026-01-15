// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>

UENUM(BlueprintType)
enum class EDeathReason : uint8
{
	Burn	UMETA(DisplayName = "Burn"),
	Smoke	UMETA(DisplayName = "Smoke")
};