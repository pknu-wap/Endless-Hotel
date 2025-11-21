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

	UPROPERTY(EditAnywhere)
	ESettingCategory Category;

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

#pragma endregion

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Button_Setting : public UUI_Button_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void SynchronizeProperties() override;

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