// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/Setting/UI_Button_Option.h"
#include <GameFramework/GameUserSettings.h>

#pragma region Declare

FHighlightEvent UUI_Button_Option::HighlightEvent;

#pragma endregion

#pragma region Base

TSharedRef<SWidget> UUI_Button_Option::RebuildWidget()
{
	TSharedRef<SWidget> Widget = Super::RebuildWidget();

	SettingHandle = UGameUserSettings::GetGameUserSettings();

	HighlightEvent.AddDynamic(this, &ThisClass::Highlight);

	OnClicked.Clear();
	OnClicked.AddDynamic(this, &ThisClass::Click_Button);

	return Widget;
}

void UUI_Button_Option::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	HighlightEvent.Clear();
}

#pragma endregion

#pragma region Click

void UUI_Button_Option::Click_Button()
{
	switch (OptionInfo.Category)
	{
	case EOptionCategory::Resolution:
		SetOption_Resolution();
		break;
	}

	HighlightEvent.Broadcast(OptionInfo);
}

#pragma endregion

#pragma region Highlight

void UUI_Button_Option::Highlight(FOptionInfo TargetInfo)
{
	if (OptionInfo.Category != TargetInfo.Category)
	{
		return;
	}

	FButtonStyle ButtonStyle = GetStyle();
	ButtonStyle.Normal.TintColor = Color_Default;

	if (OptionInfo.Value == TargetInfo.Value)
	{
		ButtonStyle.Normal.TintColor = Color_Highlight;
	}

	SetStyle(ButtonStyle);
}

#pragma endregion

#pragma region Screen

void UUI_Button_Option::SetOption_Resolution()
{
	switch (OptionInfo.Value)
	{
	case EOptionValue::HD:
		SettingHandle->SetScreenResolution(FIntPoint(1280, 720));
		break;

	case EOptionValue::FHD:
		SettingHandle->SetScreenResolution(FIntPoint(1920, 1080));
		break;

	case EOptionValue::QHD:
		SettingHandle->SetScreenResolution(FIntPoint(2560, 1440));
		break;

	case EOptionValue::UHD:
		SettingHandle->SetScreenResolution(FIntPoint(3840, 2160));
		break;
	}
}

#pragma endregion