// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/Setting/UI_Button_Setting.h"
#include "UI/PopUp/Setting/UI_PopUp_Setting.h"
#include "UI/Controller/UI_Controller.h"

#pragma region Declare

FHighlightSetting UUI_Button_Setting::HighlightSetting;

#pragma endregion

#pragma region Base

TSharedRef<SWidget> UUI_Button_Setting::RebuildWidget()
{
	HighlightSetting.AddDynamic(this, &ThisClass::Highlight);

	OnClicked.Clear();
	OnClicked.AddDynamic(this, &ThisClass::Click_Button);

	return Super::RebuildWidget();
}

void UUI_Button_Setting::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	HighlightSetting.Clear();
}

#pragma endregion

#pragma region Click

void UUI_Button_Setting::Click_Button()
{
	auto* SettingWidget = Cast<UUI_PopUp_Setting>(Owner);
	SettingWidget->ShowCategoryOption(SettingInfo.Enum);
	SettingWidget->SetCurrentCategoryText(SettingInfo.Name);
	SettingWidget->RotateGear(SettingInfo.Angle);

	HighlightSetting.Broadcast(SettingInfo);
}

#pragma endregion

#pragma region Highlight

void UUI_Button_Setting::Highlight(FSettingCategory TargetInfo)
{
	FButtonStyle ButtonStyle = GetStyle();
	ButtonStyle.Normal.TintColor = Color_Default;

	if (SettingInfo.Enum == TargetInfo.Enum)
	{
		ButtonStyle.Normal.TintColor = Color_Highlight;
	}

	SetStyle(ButtonStyle);
}

#pragma endregion