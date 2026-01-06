// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Type_UI.generated.h>

UENUM(BlueprintType)
enum class EWidgetType : uint8
{
	HUD			UMETA(DisplayName = "HUD"),
	PopUp		UMETA(DisplayName = "PopUp"),
	PopUp_Pause UMETA(DisplayName = "PopUp_Pause"),
	World		UMETA(DisplayName = "World")
};

UENUM(BlueprintType)
enum class EInputModeType : uint8
{
	None		UMETA(DisplayName = "None"),
	GameOnly	UMETA(DisplayName = "GameOnly"),
	UIOnly		UMETA(DisplayName = "UIOnly"),
	GameAndUI	UMETA(DisplayName = "GameAndUI")
};

UENUM(BlueprintType)
enum class ESettingButtonType : uint8
{
	Grapic		UMETA(DisplayName = "Grapic"),
	Resolution	UMETA(DisplayName = "Resolution"),
	Frame		UMETA(DisplayName = "Frame"),
	Screen		UMETA(DisplayName = "Screen"),
	Language	UMETA(DisplayName = "Language")
};

USTRUCT(BlueprintType)
struct FButtonInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 ButtonIndex;

	UPROPERTY(EditAnywhere)
	ESettingButtonType Category;

	UPROPERTY(EditAnywhere)
	int32 Value_Int;

	UPROPERTY(EditAnywhere)
	FString Value_String;

	UPROPERTY(EditAnywhere)
	FIntPoint Value_IntPoint;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EWindowMode::Type> Value_WindowMode;

	UPROPERTY(EditAnywhere)
	float Value_Float;
};