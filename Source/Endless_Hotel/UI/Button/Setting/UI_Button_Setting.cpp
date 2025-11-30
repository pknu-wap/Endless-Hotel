// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/Setting/UI_Button_Setting.h"
#include "UI/PopUp/Default/Setting/UI_PopUp_Setting.h"

#pragma region Base

void UUI_Button_Setting::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	OnClicked.Clear();
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
		UUI_PopUp_Setting::SettingGrapic.Broadcast(ButtonInfo);
		BtnOwner->HighlightButton(ESettingCategory::Grapic, ButtonInfo.ButtonIndex);
		break;

	case ESettingCategory::Resolution:
		UUI_PopUp_Setting::SettingResolution.Broadcast(ButtonInfo);
		BtnOwner->HighlightButton(ESettingCategory::Resolution, ButtonInfo.ButtonIndex);
		break;

	case ESettingCategory::Frame:
		UUI_PopUp_Setting::SettingFrame.Broadcast(ButtonInfo);
		BtnOwner->HighlightButton(ESettingCategory::Frame, ButtonInfo.ButtonIndex);
		break;

	case ESettingCategory::Screen:
		UUI_PopUp_Setting::SettingScreen.Broadcast(ButtonInfo);
		BtnOwner->HighlightButton(ESettingCategory::Screen, ButtonInfo.ButtonIndex);
		break;
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