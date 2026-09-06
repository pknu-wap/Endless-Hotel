// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Type_Setting.generated.h>

UENUM(BlueprintType)
enum class ESettingCategory : uint8
{
	None			UMETA(DisplayName = "None"),
	Screen			UMETA(DisplayName = "Screen"),
	Grapic			UMETA(DisplayName = "Grapic"),
	Sound			UMETA(DisplayName = "Sound"),
	Control_Normal	UMETA(DisplayName = "Control_Normal"),
	Control_Input	UMETA(DisplayName = "Control_Input"),
	Gameplay		UMETA(DisplayName = "Gameplay"),
	System			UMETA(DisplayName = "System")
};

USTRUCT(BlueprintType)
struct FCategoryButtonInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Setting")
	ESettingCategory Category = ESettingCategory::None;

	UPROPERTY(EditAnywhere, Category = "Setting")
	float Angle = 0;
};

UENUM(BlueprintType)
enum class EOptionValue : uint8
{
	Low					UMETA(DisplayName = "Low"),
	Medium				UMETA(DisplayName = "Medium"),
	High				UMETA(DisplayName = "High"),
	Epic				UMETA(DisplayName = "Epic"),
	Custom				UMETA(DisplayName = "Custom"),
	None				UMETA(DisplayName = "None"),
	On					UMETA(DisplayName = "On"),
	Off					UMETA(DisplayName = "Off"),
	HD					UMETA(DisplayName = "1280 X 720 (HD)"),
	FHD					UMETA(DisplayName = "1920 X 1080 (FHD)"),
	QHD					UMETA(DisplayName = "2560 X 1440 (QHD)"),
	UHD					UMETA(DisplayName = "3840 X 2160 (UHD)"),
	Windowed			UMETA(DisplayName = "Windowed"),
	FullScreen			UMETA(DisplayName = "FullScreen"),
	WindowedFullScreen	UMETA(DisplayName = "Windowed FullScreen"),
	W16H9				UMETA(DisplayName = "16:9"),
	W21H9				UMETA(DisplayName = "21:9"),
	W4H3				UMETA(DisplayName = "4:3"),
	W16H10				UMETA(DisplayName = "16:10"),
	English				UMETA(DisplayName = "English"),
	Korean				UMETA(DisplayName = "한국어")
};

UENUM(BlueprintType)
enum class EOptionCategory : uint8
{
	None				UMETA(DisplayName = "None"),

	// Screen
	Resolution			UMETA(DisplayName = "Resolution"),
	Window				UMETA(DisplayName = "Window"),
	Aspect				UMETA(DisplayName = "Aspect"),
	Frame				UMETA(DisplayName = "Frame"),
	VSync				UMETA(DisplayName = "VSync"),
	HDR					UMETA(DisplayName = "HDR"),

	// Grapic
	Grapic				UMETA(DisplayName = "Grapic"),
	AntiAliasing		UMETA(DisplayName = "AntiAliasing"),
	Shadow				UMETA(DisplayName = "Shadow"),
	Texture				UMETA(DisplayName = "Texture"),
	PostProcessing		UMETA(DisplayName = "PostProcessing"),
	Shading				UMETA(DisplayName = "Shading"),

	// Sound
	Master				UMETA(DisplayName = "Master"),
	BGM					UMETA(DisplayName = "BGM"),
	SFX					UMETA(DisplayName = "SFX"),
	Voice				UMETA(DisplayName = "Voice"),
	UI					UMETA(DisplayName = "UI"),

	// Control
	Sensitivity			UMETA(DisplayName = "Sensitivity"),

	// Gameplay
	Overlap				UMETA(DisplayName = "Overlap"),
	CameraShake			UMETA(DisplayName = "CameraShake"),
	WrongCheck			UMETA(DisplayName = "WrongCheck"),
	Brightness			UMETA(DisplayName = "Brightness"),

	// System
	Reset_Progression	UMETA(DisplayName = "Reset Progression"),
	Reset_Setting		UMETA(DisplayName = "Reset Setting"),
	Language			UMETA(DisplayName = "Language")
};

USTRUCT(BlueprintType)
struct FOptionValuePair
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Value")
	EOptionValue Value;

	UPROPERTY(EditDefaultsOnly, Category = "Translation")
	FText Translation;
};

USTRUCT(BlueprintType)
struct FOptionData
{
	GENERATED_BODY()


public:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSoftClassPtr<class UUI_Base> Class;

	UPROPERTY(EditDefaultsOnly, Category = "Option")
	FText Name;

	UPROPERTY(EditDefaultsOnly, Category = "Option")
	EOptionCategory Category = EOptionCategory::None;

	UPROPERTY(EditDefaultsOnly, Category = "Option")
	TArray<FOptionValuePair> Values;
};

USTRUCT(BlueprintType)
struct FOptionList
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Class")
	TSoftClassPtr<class UUI_PopUp_Option> Class;

	UPROPERTY(EditDefaultsOnly, Category = "Category")
	FText Name;

	UPROPERTY(EditDefaultsOnly, Category = "List")
	TArray<FOptionData> List;
};

UENUM(BlueprintType)
enum class EKeySettingType : uint8
{
	None		UMETA(DisplayName = "None"),
	Up			UMETA(DisplayName = "Up"),
	Down		UMETA(DisplayName = "Down"),
	Left		UMETA(DisplayName = "Left"),
	Right		UMETA(DisplayName = "Right"),
	Run			UMETA(DisplayName = "Run"),
	Sit			UMETA(DisplayName = "Sit"),
	Interact	UMETA(DisplayName = "Interact"),
	Hide		UMETA(DisplayName = "Hide"),
	Lighter		UMETA(DisplayName = "Lighter"),
	Reset		UMETA(DisplayName = "Reset")
};

USTRUCT(BlueprintType)
struct FKeySettingInfo
{
	GENERATED_BODY()

public:
	FKeySettingInfo() {}
	FKeySettingInfo(const EKeySettingType& Type, const FKey& Value) :Type(Type), Value(Value) {}

public:
	UPROPERTY(EditAnywhere, Category = "Setting")
	EKeySettingType Type = EKeySettingType::None;

	UPROPERTY(EditAnywhere, Category = "Setting")
	FKey Value;
};