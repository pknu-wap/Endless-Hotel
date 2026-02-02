// Copyright by 2025-2 WAP Game 2 team

#include "UI/ComboBox/Setting/UI_ComboBox_Setting.h"
#include "UI/PopUp/Setting/UI_PopUp_Setting.h"
#include "UI/Button/Setting/UI_Button_Option.h"
#include "Type/Save/Type_Save.h"
#include <GameFramework/GameUserSettings.h>
#include <Components/Border.h>
#include <Internationalization/Internationalization.h>

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

	case EOptionCategory::Grapic:
		SetOption_Grapic(NameValue);
		break;

	case EOptionCategory::Language:
		SetOption_Language(NameValue);
		break;
	}
}

#pragma endregion

#pragma region Screen

void UUI_ComboBox_Setting::SetOption_Resolution(FName OptionValue)
{
	UGameUserSettings* SettingHandle = UGameUserSettings::GetGameUserSettings();
	UEnum* EnumObj = StaticEnum<EOptionValue>();
	EOptionValue Value = static_cast<EOptionValue>(EnumObj->GetValueByName(OptionValue));

	auto* UI_Setting = GetTypedOuter<UUI_PopUp_Setting>();
	FSaveData_Setting& Data = UI_Setting->Data_Setting;
	Data.Resolution = Value;

	switch (Value)
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

#pragma region Grapic

void UUI_ComboBox_Setting::SetOption_Grapic(FName OptionValue)
{
	UGameUserSettings* SettingHandle = UGameUserSettings::GetGameUserSettings();
	UEnum* EnumObj = StaticEnum<EOptionValue>();
	int64 Index = EnumObj->GetIndexByName(OptionValue);
	EOptionValue Value = static_cast<EOptionValue>(EnumObj->GetValueByName(OptionValue));

	auto* UI_Setting = GetTypedOuter<UUI_PopUp_Setting>();
	FSaveData_Setting& Data = UI_Setting->Data_Setting;
	Data.Grapic = Value;

	switch (Value)
	{
	case EOptionValue::Custom:
		UI_Setting->SetHideBoxVisibility(ESlateVisibility::Hidden);
		break;

	default:
		UI_Setting->SetHideBoxVisibility(ESlateVisibility::Visible);
		SettingHandle->SetOverallScalabilityLevel(Index);

		UUI_Button_Option::HighlightOption.Broadcast(FOptionInfo(EOptionCategory::AntiAliasing, Value));
		UUI_Button_Option::HighlightOption.Broadcast(FOptionInfo(EOptionCategory::Shadow, Value));
		UUI_Button_Option::HighlightOption.Broadcast(FOptionInfo(EOptionCategory::Texture, Value));
		UUI_Button_Option::HighlightOption.Broadcast(FOptionInfo(EOptionCategory::PostProcessing, Value));
		UUI_Button_Option::HighlightOption.Broadcast(FOptionInfo(EOptionCategory::Shading, Value));
		break;
	}
}

#pragma endregion

#pragma region System

void UUI_ComboBox_Setting::SetOption_Language(FName OptionValue)
{
	UEnum* EnumObj = StaticEnum<EOptionValue>();
	EOptionValue Value = static_cast<EOptionValue>(EnumObj->GetValueByName(OptionValue));

	auto* UI_Setting = GetTypedOuter<UUI_PopUp_Setting>();
	FSaveData_Setting& Data = UI_Setting->Data_Setting;
	Data.Language = Value;

	switch (Value)
	{
	case EOptionValue::English:
		FInternationalization::Get().SetCurrentCulture(TEXT("en-US"));
		break;

	case EOptionValue::Korean:
		FInternationalization::Get().SetCurrentCulture(TEXT("ko-KR"));
		break;
	}
}

#pragma endregion