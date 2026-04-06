// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>

UENUM(BlueprintType)
enum class EAnomalyRule : uint8
{
	None				= 0		UMETA(DisplayName = "None"),
	EightExit			= 1		UMETA(DisplayName = "EightExit"),
};