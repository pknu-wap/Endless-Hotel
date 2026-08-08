// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>

UENUM(BlueprintType)
enum class EAnomalyRule : uint8
{
	None				= 0		UMETA(DisplayName = "None"),
	EightExit			= 1		UMETA(DisplayName = "EightExit"),
	Touch				= 2		UMETA(DisplayName = "Touch"),
	Doll				= 3		UMETA(DisplayName = "Doll"),
	Painting			= 4		UMETA(DispalyName = "Painting"),
	TurnOffSound		= 5		UMETA(DisplayName = "TurnOffSound"),
	ResetObject			= 6		UMETA(DisplayName = "ResetObject"),
	Watch				= 7		UMETA(DisplayName = "Watch")
};