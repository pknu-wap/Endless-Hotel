// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/Button/UI_Button_Base.h"
#include "Type/UI/Type_UI_Key.h"
#include <CoreMinimal.h>
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
	void SetSavedOption();

#pragma endregion

};