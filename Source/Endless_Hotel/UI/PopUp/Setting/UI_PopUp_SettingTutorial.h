// Copyright by 2026-1 WAP Game 2 team

#pragma once

#include "UI/PopUp/UI_PopUp_Base.h"
#include <CoreMinimal.h>
#include <UI_PopUp_SettingTutorial.generated.h>

UCLASS(Meta = (DisableNativeTick))
class ENDLESS_HOTEL_API UUI_PopUp_SettingTutorial : public UUI_PopUp_Base
{
	GENERATED_BODY()
	
#pragma region Base

protected:
	virtual void NativeOnInitialized() override;

#pragma endregion

#pragma region Show

public:
	virtual void ShowWidget() override;

#pragma endregion

#pragma region CheckBox

private:
	UFUNCTION()
	void Click_CheckBox(bool bCheck);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCheckBox> CheckBox_Show;

#pragma endregion

#pragma region Button

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> Button_YES;

#pragma endregion

};