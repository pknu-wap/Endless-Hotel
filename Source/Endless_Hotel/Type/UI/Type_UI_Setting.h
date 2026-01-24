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