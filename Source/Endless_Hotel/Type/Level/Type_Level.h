// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>

UENUM(BlueprintType)
enum class EMapDataLayer : uint8
{
	None		UMETA(DisplayName = "None"),
	Default		UMETA(DisplayName = "Default"),
	Lobby		UMETA(DisplayName = "Lobby"),
	Hotel		UMETA(DisplayName = "Hotel"),
	Fire		UMETA(DisplayName = "Fire"),
	Maze		UMETA(DisplayName = "Maze"),
	Choice		UMETA(DisplayName = "Choice")
};