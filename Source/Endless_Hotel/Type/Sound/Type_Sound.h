// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>

UENUM(BlueprintType)
enum class ESoundClassType : uint8
{
	Master	UMETA(DisplayName = "Master"),
	BGM		UMETA(DisplayName = "BGM"),
	SFX		UMETA(DisplayName = "SFX"),
	UI		UMETA(DisplayName = "UI"),
	Voice	UMETA(DisplayName = "Voice")
};