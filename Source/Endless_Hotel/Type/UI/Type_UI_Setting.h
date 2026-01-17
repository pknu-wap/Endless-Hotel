// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Type_UI_Setting.generated.h>

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
struct FSettingButtonInfo
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