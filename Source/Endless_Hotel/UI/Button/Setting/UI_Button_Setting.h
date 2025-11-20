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
	Resolution	UMETA(DisplayName = "Resolution"),
	Frame		UMETA(DisplayName = "Frame"),
	Screen		UMETA(DisplayName = "Screen"),
	Sound		UMETA(DisplayName = "Sound"),
	Brightness	UMETA(DisplayName = "Brightness"),
	Language	UMETA(DisplayName = "Language")
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

UCLASS(Meta = (DisableNativeTick))
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

#pragma region Highlight

public:
	void HighlightButton();
	void UnhighlightButton();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTexture2D> Texture_Normal;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTexture2D> Texture_Highlight;

#pragma endregion

};