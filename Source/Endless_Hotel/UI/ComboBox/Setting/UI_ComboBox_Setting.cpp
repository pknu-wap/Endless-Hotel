// Copyright by 2025-2 WAP Game 2 team

#include "UI/ComboBox/Setting/UI_ComboBox_Setting.h"
#include <GameFramework/GameUserSettings.h>
#include <Components/Border.h>

#pragma region Active

void UUI_ComboBox_Setting::ActiveComboBox()
{
	UBorder* Outline = Cast<UBorder>(GetParent());

	FSlateBrush& Brush = Outline->Background;
	Brush.DrawAs = ESlateBrushDrawType::RoundedBox;
	Brush.OutlineSettings.Color = OutlineColor_Focus;
	Brush.OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
	Outline->SetBrush(Brush);
}

void UUI_ComboBox_Setting::DeactiveComboBox(FName NameValue, ESelectInfo::Type EnumValue)
{
	UBorder* Outline = Cast<UBorder>(GetParent());

	FSlateBrush& Brush = Outline->Background;
	Brush.DrawAs = ESlateBrushDrawType::RoundedBox;
	Brush.OutlineSettings.Color = OutlineColor_Normal;
	Brush.OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
	Outline->SetBrush(Brush);

	switch (OptionCategory)
	{
	case EOptionCategory::Resolution:
		SetOption_Resolution(NameValue);
		break;
	}
}

#pragma endregion

#pragma region Screen

void UUI_ComboBox_Setting::SetOption_Resolution(FName OptionValue)
{
	UGameUserSettings* SettingHandle = UGameUserSettings::GetGameUserSettings();

	UEnum* EnumObj = StaticEnum<EOptionValue>();
	const EOptionValue& EnumValue = static_cast<EOptionValue>(EnumObj->GetValueByName(OptionValue));
	
	FText OptionText = FText::FromName(OptionValue);
	if (EnumObj->GetDisplayNameTextByValue(static_cast<int64>(EOptionValue::HD)).EqualTo(OptionText))
	{
		SettingHandle->SetScreenResolution(FIntPoint(1280, 720));
	}
	else if (EnumObj->GetDisplayNameTextByValue(static_cast<int64>(EOptionValue::FHD)).EqualTo(OptionText))
	{
		SettingHandle->SetScreenResolution(FIntPoint(1920, 1080));
	}
	else if (EnumObj->GetDisplayNameTextByValue(static_cast<int64>(EOptionValue::QHD)).EqualTo(OptionText))
	{
		SettingHandle->SetScreenResolution(FIntPoint(2560, 1440));
	}
	else if (EnumObj->GetDisplayNameTextByValue(static_cast<int64>(EOptionValue::UHD)).EqualTo(OptionText))
	{
		SettingHandle->SetScreenResolution(FIntPoint(3840, 2160));
	}
}

#pragma endregion