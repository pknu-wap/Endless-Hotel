// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>

UENUM(BlueprintType)
enum class ECameraType : uint8
{
	None		UMETA(DisplayName = "None"),
	Title		UMETA(DisplayName = "Title"),
	Gear		UMETA(DisplayName = "Gear"),
	SandClock	UMETA(DisplayName = "SandClock")
};