// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Type_Save.generated.h>

USTRUCT(BlueprintType)
struct FSettingSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY(SaveGame)
	int32 Value_Grapic;

	UPROPERTY(SaveGame)
	FIntPoint Value_Resolution;

	UPROPERTY(SaveGame)
	uint8 Value_Screen;

	UPROPERTY(SaveGame)
	float Value_Frame;

	UPROPERTY(SaveGame)
	float Value_Sound = 0.5f;

	UPROPERTY(SaveGame)
	float Value_Sensitivity = 0.5f;

	UPROPERTY(SaveGame)
	float Value_Brightness = 1;

	UPROPERTY(SaveGame)
	FString Value_Language;

public:
	UPROPERTY(SaveGame)
	int32 Index_Grapic;

	UPROPERTY(SaveGame)
	int32 Index_Resolution;

	UPROPERTY(SaveGame)
	int32 Index_Screen;

	UPROPERTY(SaveGame)
	int32 Index_Frame;

	UPROPERTY(SaveGame)
	int32 Index_Language;
};