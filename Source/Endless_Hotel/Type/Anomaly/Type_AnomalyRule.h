// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>

UENUM(BlueprintType)
enum class EAnomalyRule : uint8
{
	None				= 0		UMETA(DisplayName = "None"),
	EightExit			= 1		UMETA(DisplayName = "EightExit"),
	TurnOffSound		= 2		UMETA(DisplayName = "TurnOffSound"),
	Monster				= 4		UMETA(DisplayName = "Monster"),
	Painting			= 5		UMETA(DispalyName = "Painting"),
	Doll				= 6		UMETA(DisplayName = "Doll"),
	ResetObject			= 7		UMETA(DisplayName = "ResetObject")
};