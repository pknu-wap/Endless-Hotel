// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/Button/UI_Button_Base.h"
#include "Type/UI/Type_Setting.h"
#include <CoreMinimal.h>
#include <Delegates/DelegateCombinations.h>
#include <UI_Button_Key.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Button_Key : public UUI_Button_Base
{
	GENERATED_BODY()

#pragma region Bind

public:
	void BindEvents();

#pragma endregion

#pragma region Key

protected:
	UPROPERTY(EditAnywhere, Category = "Setting|Key")
	FKeySettingInfo SettingInfo;

#pragma endregion

#pragma region Reset

protected:
	UFUNCTION()
	void ResetInputButtons();

#pragma endregion

#pragma region Selector

protected:
	UFUNCTION()
	void SelectedKeyValue(FInputChord SelectedChord);

	void ConvertLongText(FInputChord SelectedChord);

protected:
	UPROPERTY()
	TObjectPtr<class UInputKeySelector> Selector;

#pragma endregion

#pragma region Highlight

public:
	UFUNCTION()
	void SetSavedOption();

protected:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FKeyHighlight);
	static FKeyHighlight Highlight;

#pragma endregion

};