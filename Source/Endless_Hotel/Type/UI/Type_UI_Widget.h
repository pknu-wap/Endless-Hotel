// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>

UENUM(BlueprintType)
enum class EWidgetType : uint8
{
	None		UMETA(DisplayName = "None"),
	HUD			UMETA(DisplayName = "HUD"),
	PopUp		UMETA(DisplayName = "PopUp"),
	PopUp_Pause UMETA(DisplayName = "PopUp_Pause")
};

UENUM(BlueprintType)
enum class EInputModeType : uint8
{
	None		UMETA(DisplayName = "None"),
	GameOnly	UMETA(DisplayName = "GameOnly"),
	UIOnly		UMETA(DisplayName = "UIOnly"),
	GameAndUI	UMETA(DisplayName = "GameAndUI")
};