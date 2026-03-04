// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "Type/UI/Type_UI_Setting.h"
#include "Type/UI/Type_UI_Key.h"
#include <CoreMinimal.h>
#include <Type_Save.generated.h>

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
	float Interface = 0.5f;

	UPROPERTY(SaveGame)
	uint8 EnableMaster = 1;

	UPROPERTY(SaveGame)
	uint8 EnableBGM = 1;

	UPROPERTY(SaveGame)
	uint8 EnableSFX = 1;

	UPROPERTY(SaveGame)
	uint8 EnableVoice = 1;

	UPROPERTY(SaveGame)
	uint8 EnableInterface = 1;

public:
	// Control
	UPROPERTY(SaveGame)
	float Sensitivity = 0.5f;

public:
	// Gameplay
	UPROPERTY(SaveGame)
	EOptionValue Overlap = EOptionValue::Off;

	UPROPERTY(SaveGame)
	float Brightness = 0.5f;

public:
	// System
	UPROPERTY(SaveGame)
	EOptionValue Language = EOptionValue::Korean;
};

USTRUCT()
struct FSaveData_Key
{
	GENERATED_BODY()

public:
	UPROPERTY(SaveGame)
	FKeySettingInfo Up = FKeySettingInfo(EKeySettingType::Up, EKeys::W);

	UPROPERTY(SaveGame)
	FKeySettingInfo Down = FKeySettingInfo(EKeySettingType::Up, EKeys::S);

	UPROPERTY(SaveGame)
	FKeySettingInfo Left = FKeySettingInfo(EKeySettingType::Up, EKeys::A);

	UPROPERTY(SaveGame)
	FKeySettingInfo Right = FKeySettingInfo(EKeySettingType::Up, EKeys::D);

	UPROPERTY(SaveGame)
	FKeySettingInfo Run = FKeySettingInfo(EKeySettingType::Up, EKeys::LeftShift);

	UPROPERTY(SaveGame)
	FKeySettingInfo Sit = FKeySettingInfo(EKeySettingType::Up, EKeys::SpaceBar);

	UPROPERTY(SaveGame)
	FKeySettingInfo Interact = FKeySettingInfo(EKeySettingType::Up, EKeys::E);

	UPROPERTY(SaveGame)
	FKeySettingInfo Hide = FKeySettingInfo(EKeySettingType::Up, EKeys::RightMouseButton);

	UPROPERTY(SaveGame)
	FKeySettingInfo Flash = FKeySettingInfo(EKeySettingType::Up, EKeys::Q);
};