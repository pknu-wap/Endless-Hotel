// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/UI/Type_Setting.h"
#include "Type/Anomaly/Type_AnomalyRule.h"
#include <CoreMinimal.h>
#include <Type_Save.generated.h>

#pragma region Setting

USTRUCT()
struct FSaveData_Setting
{
	GENERATED_BODY()

public:
	// Screen
	UPROPERTY(SaveGame)
	EOptionValue Resolution = EOptionValue::FHD;

	UPROPERTY(SaveGame)
	EOptionValue Window = EOptionValue::FullScreen;

	UPROPERTY(SaveGame)
	EOptionValue Aspect = EOptionValue::W16H9;

	UPROPERTY(SaveGame)
	EOptionValue Frame = EOptionValue::High;

	UPROPERTY(SaveGame)
	EOptionValue VSync = EOptionValue::On;

	UPROPERTY(SaveGame)
	EOptionValue HDR = EOptionValue::On;

public:
	// Grapic
	UPROPERTY(SaveGame)
	EOptionValue Grapic = EOptionValue::Epic;

	UPROPERTY(SaveGame)
	EOptionValue AntiAliasing = EOptionValue::Epic;

	UPROPERTY(SaveGame)
	EOptionValue Shadow = EOptionValue::Epic;

	UPROPERTY(SaveGame)
	EOptionValue Texture = EOptionValue::Epic;

	UPROPERTY(SaveGame)
	EOptionValue PostProcessing = EOptionValue::Epic;

	UPROPERTY(SaveGame)
	EOptionValue Shading = EOptionValue::Epic;

public:
	// Sound
	UPROPERTY(SaveGame)
	float Master = 0.5f;

	UPROPERTY(SaveGame)
	float BGM = 0.5f;

	UPROPERTY(SaveGame)
	float SFX = 0.5f;

	UPROPERTY(SaveGame)
	float Voice = 0.5f;

	UPROPERTY(SaveGame)
	float UI = 0.5f;

	UPROPERTY(SaveGame)
	uint8 MuteMaster = 0;

	UPROPERTY(SaveGame)
	uint8 MuteBGM = 0;

	UPROPERTY(SaveGame)
	uint8 MuteSFX = 0;

	UPROPERTY(SaveGame)
	uint8 MuteVoice = 0;

	UPROPERTY(SaveGame)
	uint8 MuteUI = 0;

public:
	// Control
	UPROPERTY(SaveGame)
	float Sensitivity = 0.5f;

public:
	// Gameplay
	UPROPERTY(SaveGame)
	EOptionValue Overlap = EOptionValue::Off;

	UPROPERTY(SaveGame)
	EOptionValue CameraShake = EOptionValue::On;

	UPROPERTY(SaveGame)
	float Brightness = 1.f;

public:
	// System
	UPROPERTY(SaveGame)
	EOptionValue Language = EOptionValue::Korean;

public:
	// Keyboard
	void ResetKeySetting()
	{
		Up = FKeySettingInfo(EKeySettingType::Up, EKeys::W);
		Down = FKeySettingInfo(EKeySettingType::Down, EKeys::S);
		Left = FKeySettingInfo(EKeySettingType::Left, EKeys::A);
		Right = FKeySettingInfo(EKeySettingType::Right, EKeys::D);
		Run = FKeySettingInfo(EKeySettingType::Run, EKeys::LeftShift);
		Sit = FKeySettingInfo(EKeySettingType::Sit, EKeys::SpaceBar);
		Interact = FKeySettingInfo(EKeySettingType::Interact, EKeys::E);
		Hide = FKeySettingInfo(EKeySettingType::Hide, EKeys::RightMouseButton);
		Lighter = FKeySettingInfo(EKeySettingType::Lighter, EKeys::Q);
	}

public:
	// Keyboard
	UPROPERTY(SaveGame)
	FKeySettingInfo Up = FKeySettingInfo(EKeySettingType::Up, EKeys::W);

	UPROPERTY(SaveGame)
	FKeySettingInfo Down = FKeySettingInfo(EKeySettingType::Down, EKeys::S);

	UPROPERTY(SaveGame)
	FKeySettingInfo Left = FKeySettingInfo(EKeySettingType::Left, EKeys::A);

	UPROPERTY(SaveGame)
	FKeySettingInfo Right = FKeySettingInfo(EKeySettingType::Right, EKeys::D);

	UPROPERTY(SaveGame)
	FKeySettingInfo Run = FKeySettingInfo(EKeySettingType::Run, EKeys::LeftShift);

	UPROPERTY(SaveGame)
	FKeySettingInfo Sit = FKeySettingInfo(EKeySettingType::Sit, EKeys::SpaceBar);

	UPROPERTY(SaveGame)
	FKeySettingInfo Interact = FKeySettingInfo(EKeySettingType::Interact, EKeys::E);

	UPROPERTY(SaveGame)
	FKeySettingInfo Hide = FKeySettingInfo(EKeySettingType::Hide, EKeys::RightMouseButton);

	UPROPERTY(SaveGame)
	FKeySettingInfo Lighter = FKeySettingInfo(EKeySettingType::Lighter, EKeys::Q);
};

#pragma endregion

#pragma region Progression

UENUM(BlueprintType)
enum class EGameProgression : uint8
{
	CheckIn		UMETA(DisplayName = "CheckIn"),
	Tutorial	UMETA(DisplayName = "Tutorial"),
	Loop		UMETA(DisplayName = "Loop")
};

USTRUCT()
struct FSaveData_Progression
{
	GENERATED_BODY()

public:
	UPROPERTY(SaveGame)
	bool bGameClear = false;

	UPROPERTY(SaveGame)
	EGameProgression Progression = EGameProgression::Tutorial;

	UPROPERTY(SaveGame)
	bool bHasFlash = false;

	UPROPERTY(SaveGame)
	bool bHasKey = false;

	UPROPERTY(SaveGame)
	bool bReadManual = false;

	UPROPERTY(SaveGame)
	TArray<EAnomalyRule> ActiveRules = { EAnomalyRule::NoAnomaly, EAnomalyRule::EightExit, EAnomalyRule::Touch, EAnomalyRule::Watch };
};

#pragma endregion