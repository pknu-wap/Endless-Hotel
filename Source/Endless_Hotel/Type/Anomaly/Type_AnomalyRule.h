// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>

UENUM(BlueprintType)
enum class EAnomalyRule : uint8
{
	None				= 0		UMETA(DisplayName = "None"),
	EightExit			= 1		UMETA(DisplayName = "EightExit"),
	TurnOffSound		= 2		UMETA(DisplayName = "TurnOffSound"),
	Painting			= 3		UMETA(DispalyName = "Painting"),
	Doll				= 4		UMETA(DisplayName = "Doll"),
	ResetObject			= 5		UMETA(DisplayName = "ResetObject"),
	Watch				= 6		UMETA(DisplayName = "Watch")
};