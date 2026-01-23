// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Setting/UI_PopUp_Setting.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <GameFramework/GameUserSettings.h>

#pragma region Base

void UUI_PopUp_Setting::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SettingHandle = UGameUserSettings::GetGameUserSettings();

	Button_Apply->OnClicked.AddDynamic(this, &ThisClass::Click_Apply);
	Button_Cancel->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
}

#pragma endregion

#pragma region Category

void UUI_PopUp_Setting::SetCurrentCategoryText(FText Value)
{
	Text_CurrentCategory->SetText(Value);
}

#pragma endregion

#pragma region Control

void UUI_PopUp_Setting::Click_Apply()
{
	SettingHandle->ApplySettings(false);

	Input_ESC();
}

#pragma endregion