// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include <CoreMinimal.h>
#include <Type_UI_Key.generated.h>

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
	Flash		UMETA(DisplayName = "Flash"),
	Reset		UMETA(DisplayName = "Reset")
};

USTRUCT(BlueprintType)
struct FKeySettingInfo
{
	GENERATED_BODY()

public:
	FKeySettingInfo() {}
	FKeySettingInfo(const EKeySettingType& Type, const FKey& Value)
		:Type(Type), Value(Value) {}

public:
	UPROPERTY(EditAnywhere)
	EKeySettingType Type = EKeySettingType::None;

	UPROPERTY(EditAnywhere)
	FKey Value;
};