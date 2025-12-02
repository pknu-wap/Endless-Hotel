// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/Setting/UI_Button_Setting.h"
#include "UI/PopUp/Default/Setting/UI_PopUp_Setting.h"
#include "UI/PopUp/Default/Setting/UI_PopUp_Language.h"

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
	case ESettingButtonType::Grapic:
		UUI_PopUp_Setting::SettingGrapic.Broadcast(ButtonInfo);
		BtnOwner->HighlightButton(ESettingButtonType::Grapic, ButtonInfo.ButtonIndex);
		break;

	case ESettingButtonType::Resolution:
		UUI_PopUp_Setting::SettingResolution.Broadcast(ButtonInfo);
		BtnOwner->HighlightButton(ESettingButtonType::Resolution, ButtonInfo.ButtonIndex);
		break;

	case ESettingButtonType::Frame:
		UUI_PopUp_Setting::SettingFrame.Broadcast(ButtonInfo);
		BtnOwner->HighlightButton(ESettingButtonType::Frame, ButtonInfo.ButtonIndex);
		break;

	case ESettingButtonType::Screen:
		UUI_PopUp_Setting::SettingScreen.Broadcast(ButtonInfo);
		BtnOwner->HighlightButton(ESettingButtonType::Screen, ButtonInfo.ButtonIndex);
		break;

	case ESettingButtonType::Language:
		UUI_PopUp_Language::SettingLanguage.Broadcast(ButtonInfo);
		BtnOwner->
	}
}

#pragma endregion