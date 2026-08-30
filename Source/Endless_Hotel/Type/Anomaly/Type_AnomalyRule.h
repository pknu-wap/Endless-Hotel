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
	Painting			= 4		UMETA(DisplayName = "Painting"),
	TurnOffSound		= 5		UMETA(DisplayName = "TurnOffSound"),
	ResetObject			= 6		UMETA(DisplayName = "ResetObject"),
	Watch				= 7		UMETA(DisplayName = "Watch")
};

UENUM(BlueprintType)
enum class EFakeRule : uint8
{
	None				= 0		UMETA(DisplayName = "None"),
	FakePaintingBurn	= 1		UMETA(DisplayName = "FakePaintingBurn"),
	FakeDollFlip		= 2		UMETA(DisplayName = "FakeDollFlip"),
	FakeWatchTouch		= 3		UMETA(DisplayName = "FakeWatchTouch"),
};