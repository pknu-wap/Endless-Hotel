// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>

UENUM(BlueprintType)
enum class ELevelType : uint8
{
	None		UMETA(DisplayName = "None"),
	Persistent	UMETA(DisplayName = "Persistent"),
	MainMenu	UMETA(DisplayName = "MainMenu"),
	Hotel		UMETA(DisplayName = "Hotel")
};