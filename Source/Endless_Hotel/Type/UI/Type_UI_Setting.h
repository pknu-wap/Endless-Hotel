// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Type_UI_Setting.generated.h>

UENUM(BlueprintType)
enum class ESettingCategory : uint8
{
	Screen		UMETA(DisplayName = "Screen"),
	Grapic		UMETA(DisplayName = "Grapic"),
	Sound		UMETA(DisplayName = "Sound"),
	Control		UMETA(DisplayName = "Control"),
	Gameplay	UMETA(DisplayName = "Gameplay"),
	System		UMETA(DisplayName = "System")
};

USTRUCT(BlueprintType)
struct FSettingCategory
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere)
	ESettingCategory Enum;

	UPROPERTY(EditAnyWhere)
	FText Name;

	UPROPERTY(EditAnyWhere)
	float Angle;
};

UENUM(BlueprintType)
enum class EOptionValue : uint8
{
	Low					UMETA(DisplayName = "Low"),
	Medium				UMETA(DisplayName = "Medium"),
	High				UMETA(DisplayName = "High"),
	Epic				UMETA(DisplayName = "Epic"),
	Custom				UMETA(DisplayName = "Custom"),
	On					UMETA(DisplayName = "On"),
	Off					UMETA(DisplayName = "Off"),
	HD					UMETA(DisplayName = "1280 X 720 (HD)"),
	FHD					UMETA(DisplayName = "1920 X 1080 (FHD)"),
	QHD					UMETA(DisplayName = "2560 X 1440 (QHD)"),
	UHD					UMETA(DisplayName = "3840 X 2160 (UHD)"),
	Windowed			UMETA(DisplayName = "Windowed"),
	FullScreen			UMETA(DisplayName = "FullScreen"),
	WindowedFullScreen	UMETA(DisplayName = "WindowedFullScreen"),
	W16H9				UMETA(DisplayName = "16:9"),
	W21H9				UMETA(DisplayName = "21:9"),
	W4H3				UMETA(DisplayName = "4:3"),
	W16H10				UMETA(DisplayName = "16:10")
};

UENUM(BlueprintType)
enum class EOptionCategory : uint8
{
	// Screen
	Resolution		UMETA(DisplayName = "Resolution"),
	Window			UMETA(DisplayName = "Window"),
	Aspect			UMETA(DisplayName = "Aspect"),
	Frame			UMETA(DisplayName = "Frame"),
	VSync			UMETA(DisplayName = "VSync"),
	HDR				UMETA(DisplayName = "HDR"),

	// Grapic
	Grapic			UMETA(DisplayName = "Grapic"),
	AntiAliasing	UMETA(DisplayName = "AntiAliasing"),
	Shadow			UMETA(DisplayName = "Shadow"),
	Texture			UMETA(DisplayName = "Texture"),
	PostProcessing	UMETA(DisplayName = "PostProcessing"),
	Shading			UMETA(DisplayName = "Shading"),

	// Sound
	Master			UMETA(DisplayName = "Master"),
	BGM				UMETA(DisplayName = "BGM"),
	SFX				UMETA(DisplayName = "SFX"),
	Voice			UMETA(DisplayName = "Voice"),
	Interface		UMETA(DisplayName = "Interface"),

	// Control
	Sensitivity		UMETA(DisplayName = "Sensitivity")
};

USTRUCT(BlueprintType)
struct FOptionInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EOptionCategory Category;

	UPROPERTY(EditAnywhere)
	EOptionValue Value;
};