// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/Button/UI_Button_Base.h"
#include <CoreMinimal.h>
#include <UI_Button_Key.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_Button_Key : public UUI_Button_Base
{
	GENERATED_BODY()

#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Reset

private:
	UFUNCTION()
	void ResetInputButtons();

#pragma endregion

#pragma region Selector

private:
	UFUNCTION()
	void SelectedKeyValue(FInputChord SelectedChord);

	void ConvertLongText(FInputChord SelectedChord);

private:
	UPROPERTY()
	TObjectPtr<class UInputKeySelector> Selector;

#pragma endregion

#pragma region Highlight

public:
	UFUNCTION()
	void SetSavedOption();

#pragma endregion

};