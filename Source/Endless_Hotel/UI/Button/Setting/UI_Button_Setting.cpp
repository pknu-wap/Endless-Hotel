// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/Setting/UI_Button_Setting.h"
#include "UI/PopUp/Default/Setting/UI_PopUp_Setting.h"

#pragma region Base

UUI_Button_Setting::UUI_Button_Setting()
{
	OnClicked.AddDynamic(this, &ThisClass::ButtonClick);
}

#pragma endregion

#pragma region Click

void UUI_Button_Setting::ButtonClick()
{
	switch (ButtonInfo.Category)
	{
	case ESettingCategory::Grapic:
		UUI_PopUp_Setting::SettingGrapic.Broadcast(ButtonInfo.Value_Int, ButtonInfo.Highlight_Index);
		break;

	case ESettingCategory::Language:
		UUI_PopUp_Setting::SettingLanguage.Broadcast(ButtonInfo.Value_String, ButtonInfo.Highlight_Index);
		break;

	case ESettingCategory::Resolution:
		UUI_PopUp_Setting::SettingResolution.Broadcast(ButtonInfo.Value_IntPoint, ButtonInfo.Highlight_Index);
		break;

	case ESettingCategory::Screen:
		UUI_PopUp_Setting::SettingScreen.Broadcast(ButtonInfo.Value_WindowMode, ButtonInfo.Highlight_Index);
		break;
	}
}

#pragma endregion