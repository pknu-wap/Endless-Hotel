// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>

UENUM(BlueprintType)
enum class EAnomalyRule : uint8
{
	None				= 0		UMETA(DisplayName = "None"),
	NoAnomaly			= 1		UMETA(DisplayName = "NoAnomaly"),
	EightExit			= 2		UMETA(DisplayName = "EightExit"),
	Touch				= 3		UMETA(DisplayName = "Touch"),
	Doll				= 4		UMETA(DisplayName = "Doll"),
	Painting			= 5		UMETA(DisplayName = "Painting"),
	TurnOffSound		= 6		UMETA(DisplayName = "TurnOffSound"),
	ResetObject			= 7		UMETA(DisplayName = "ResetObject"),
	Watch				= 8		UMETA(DisplayName = "Watch")
};