// Copyright by 2025-2 WAP Game 2 team

#pragma once

#include "UI/Button/UI_Button_Base.h"
#include "Type/UI/Type_Setting.h"
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

#pragma region Option

private:
	UPROPERTY(EditDefaultsOnly, Category = "Option")
	FKeySettingInfo SettingInfo;

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

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UInputKeySelector> Selector;

#pragma endregion

};