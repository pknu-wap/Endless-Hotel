// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>

UENUM(BlueprintType)
enum class EQuitType : uint8
{
	Quit		UMETA(DisplayName = "Quit"),
	MainMenu	UMETA(DisplayName = "MainMenu")
};