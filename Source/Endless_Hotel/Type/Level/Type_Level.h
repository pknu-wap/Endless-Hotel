// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>

UENUM(BlueprintType)
enum class ELevelType : uint8
{
	None		UMETA(DisplayName = "None"),
	MainMenu	UMETA(DisplayName = "MainMenu"),
	Hotel		UMETA(DisplayName = "Hotel")
};

UENUM(BlueprintType)
enum class EHotelDataLayer : uint8
{
	None		UMETA(DisplayName = "None"),
	Default		UMETA(DisplayName = "Default"),
	Hotel		UMETA(DisplayName = "Hotel"),
	Fire		UMETA(DisplayName = "Fire"),
	Maze		UMETA(DisplayName = "Maze"),
	Choice		UMETA(DisplayName = "Choice")
};