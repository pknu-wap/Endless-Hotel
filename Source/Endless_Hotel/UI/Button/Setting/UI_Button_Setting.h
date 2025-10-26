// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "CoreMinimal.h"
#include "UI/Button/UI_Button_Base.h"
#include "UI_Button_Setting.generated.h"

#pragma region Declare

UENUM(BlueprintType)
enum class ESettingCategory : uint8
{
	Grapic		UMETA(DisplayName = "Grapic"),
	Language	UMETA(DisplayName = "Language"),
	Resolution	UMETA(DisplayName = "Resolution"),
	Screen		UMETA(DisplayName = "Screen"),
	Sound		UMETA(DisplayName = "Sound")
};

USTRUCT(BlueprintType)
struct FButtonInfo
{
	GENERATED_BODY()

	ESettingCategory Category;
	int32 Highlight_Index;

	int32 Value_Int;
	FString Value_String;
	FIntPoint Value_IntPoint;
	EWindowMode::Type Value_WindowMode;
	float Value_Float;
};

#pragma endregion

UCLASS()
class ENDLESS_HOTEL_API UUI_Button_Setting : public UUI_Button_Base
{
	GENERATED_BODY()

#pragma region Base

public:
	UUI_Button_Setting(const FObjectInitializer& ObjectInitializer);

#pragma endregion
	
#pragma region Setting

public:
	UPROPERTY(EditAnywhere)
	FButtonInfo ButtonInfo;

#pragma endregion

#pragma region Click

protected:
	UFUNCTION()
	void ButtonClick();

#pragma endregion

};