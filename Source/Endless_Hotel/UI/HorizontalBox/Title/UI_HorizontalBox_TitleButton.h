// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "UI/HorizontalBox/UI_HorizontalBox_Base.h"
#include <CoreMinimal.h>
#include <UI_HorizontalBox_TitleButton.generated.h>

#pragma region Enum

UENUM(BlueprintType)
enum class ETitleButtonType : uint8
{
	None		UMETA(DisplayName = "None"),
	Start		UMETA(DisplayName = "Start"),
	Setting		UMETA(DisplayName = "Setting"),
	Quit		UMETA(DisplayName = "Quit")
};

#pragma endregion

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_HorizontalBox_TitleButton : public UUI_HorizontalBox_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Type

private:
	UPROPERTY(EditAnywhere, Category = "Type")
	ETitleButtonType ButtonType = ETitleButtonType::None;

#pragma endregion

#pragma region Text

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text_Button;

	UPROPERTY(EditAnywhere, Category = "Text")
	FText ButtonName;

#pragma endregion

#pragma region Button

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button;

#pragma endregion

#pragma region Click

private:
	UFUNCTION()
	void Click_Button();

#pragma endregion

#pragma region Hover

private:
	UFUNCTION()
	void Hover_Button();

	UFUNCTION()
	void Unhover_Button();

private:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> Anim_Hover;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> Anim_Unhover;

#pragma endregion

};