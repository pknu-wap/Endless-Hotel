// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/Setting/UI_Button_Setting.h"
#include "UI/PopUp/Default/Setting/UI_PopUp_Setting.h"

#pragma region Base

UUI_Button_Setting::UUI_Button_Setting(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
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
		UUI_PopUp_Setting::SettingGrapic.Broadcast(ButtonInfo, ButtonInfo.Highlight_Index);
		break;

	case ESettingCategory::Resolution:
		UUI_PopUp_Setting::SettingResolution.Broadcast(ButtonInfo, ButtonInfo.Highlight_Index);
		break;

	case ESettingCategory::Frame:
		UUI_PopUp_Setting::SettingFrame.Broadcast(ButtonInfo, ButtonInfo.Highlight_Index);
		break;

	case ESettingCategory::Screen:
		UUI_PopUp_Setting::SettingScreen.Broadcast(ButtonInfo, ButtonInfo.Highlight_Index);
		break;

	/*case ESettingCategory::Language:
		UUI_PopUp_Setting::SettingLanguage.Broadcast(ButtonInfo, ButtonInfo.Highlight_Index);
		break;*/
	}
}

#pragma endregion