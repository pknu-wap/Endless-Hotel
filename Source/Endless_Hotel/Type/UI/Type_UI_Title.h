// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>

UENUM(BlueprintType)
enum class ETitleButtonType : uint8
{
	None	UMETA(DisplayName = "None"),
	Start	UMETA(DisplayName = "Start"),
	Setting	UMETA(DisplayName = "Setting"),
	Quit	UMETA(DisplayName = "Quit")
};