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
	auto* BtnOwner = Cast<UUI_PopUp_Setting>(ButtonOwner);

	switch (ButtonInfo.Category)
	{
	case ESettingCategory::Grapic:
		UUI_PopUp_Setting::SettingGrapic.Broadcast(ButtonInfo, ButtonInfo.Highlight_Index);
		BtnOwner->HighlightButton(ESettingCategory::Grapic, ButtonIndex);
		break;

	case ESettingCategory::Resolution:
		UUI_PopUp_Setting::SettingResolution.Broadcast(ButtonInfo, ButtonInfo.Highlight_Index);
		BtnOwner->HighlightButton(ESettingCategory::Resolution, ButtonIndex);
		break;

	case ESettingCategory::Frame:
		UUI_PopUp_Setting::SettingFrame.Broadcast(ButtonInfo, ButtonInfo.Highlight_Index);
		BtnOwner->HighlightButton(ESettingCategory::Frame, ButtonIndex);
		break;

	case ESettingCategory::Screen:
		UUI_PopUp_Setting::SettingScreen.Broadcast(ButtonInfo, ButtonInfo.Highlight_Index);
		BtnOwner->HighlightButton(ESettingCategory::Screen, ButtonIndex);
		break;

	/*case ESettingCategory::Language:
		UUI_PopUp_Setting::SettingLanguage.Broadcast(ButtonInfo, ButtonInfo.Highlight_Index);
		BtnOwner->HighlightButton(ESettingCategory::Language, ButtonIndex);
		break;*/
	}
}

#pragma endregion

#pragma region Hightlight

void UUI_Button_Setting::HighlightButton()
{
	FSlateBrush Brush;
	Brush.SetResourceObject(Texture_Highlight);
	WidgetStyle.SetNormal(Brush);
}

void UUI_Button_Setting::UnhighlightButton()
{
	FSlateBrush Brush;
	Brush.SetResourceObject(Texture_Normal);
	WidgetStyle.SetNormal(Brush);
}

#pragma endregion