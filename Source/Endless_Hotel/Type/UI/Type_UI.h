// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>

UENUM(BlueprintType)
enum class EWidgetType : uint8
{
	None					UMETA(DisplayName = "None"),
	HUD_InGame				UMETA(DisplayName = "HUD_InGame"),
	HUD_Title				UMETA(DisplayName = "HUD_Title"),
	HUD_Loading				UMETA(DisplayName = "HUD_Loading"),
	PopUp_Escape			UMETA(DisplayName = "PopUp_Escape"),
	PopUp_Setting			UMETA(DisplayName = "PopUp_Setting"),
	PopUp_Read				UMETA(DisplayName = "PopUp_Read"),
	PopUp_NoteBook			UMETA(DisplayName = "PopUp_NoteBook"),
	PopUp_ResetNote			UMETA(DisplayName = "PopUp_ResetNote"),
	PopUp_ResetSetting		UMETA(DisplayName = "PopUp_ResetSetting"),
	PopUp_MainMenuCheck		UMETA(DisplayName = "PopUp_MainMenuCheck"),
	PopUp_QuitCheck			UMETA(DisplayName = "PopUp_QuitCheck"),
	PopUp_Tutorial			UMETA(DisplayName = "PopUp_Tutorial"),
	PopUp_Manual			UMETA(DisplayName = "PopUp_Manual"),
	PopUp_Acquire			UMETA(DisplayName = "PopUp_Acquire"),
	PopUp_Demo				UMETA(DisplayName = "PopUp_Demo"),
	PopUp_Demo_QR			UMETA(DisplayName = "PopUp_Demo_QR")
};

UENUM(BlueprintType)
enum class EWidgetLayer : uint8
{
	None		UMETA(DisplayName = "None"),
	HUD			UMETA(DisplayName = "HUD"),
	PopUp		UMETA(DisplayName = "PopUp"),
	PopUp_Pause UMETA(DisplayName = "PopUp_Pause")
};

UENUM(BlueprintType)
enum class EWidgetInputMode : uint8
{
	None		UMETA(DisplayName = "None"),
	GameOnly	UMETA(DisplayName = "GameOnly"),
	UIOnly		UMETA(DisplayName = "UIOnly"),
	GameAndUI	UMETA(DisplayName = "GameAndUI")
};