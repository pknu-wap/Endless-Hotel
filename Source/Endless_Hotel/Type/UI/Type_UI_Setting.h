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
	TSubclassOf<class UUI_Base> Class;

	UPROPERTY(EditAnyWhere)
	float Angle;
};

UENUM(BlueprintType)
enum class EOptionValue : uint8
{
	None				UMETA(DisplayName = "None"),
	On					UMETA(DisplayName = "On"),
	Off					UMETA(DisplayName = "Off"),
	Low					UMETA(DisplayName = "Low"),
	Medium				UMETA(DisplayName = "Medium"),
	High				UMETA(DisplayName = "High"),
	Epic				UMETA(DisplayName = "Epic"),
	HD					UMETA(DisplayName = "HD"),
	FHD					UMETA(DisplayName = "FHD"),
	QHD					UMETA(DisplayName = "QHD"),
	UHD					UMETA(DisplayName = "UHD"),
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
	Resolution	UMETA(DisplayName = "Resolution"),
	Window		UMETA(DisplayName = "Window"),
	Aspect		UMETA(DisplayName = "Aspect"),
	Frame		UMETA(DisplayName = "Frame"),
	VSync		UMETA(DisplayName = "VSync"),
	HDR			UMETA(DisplayName = "HDR")
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