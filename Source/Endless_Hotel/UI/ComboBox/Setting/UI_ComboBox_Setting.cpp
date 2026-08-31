// Copyright by 2025-2 WAP Game 2 team

#include "UI/ComboBox/Setting/UI_ComboBox_Setting.h"
#include "UI/PopUp/Setting/UI_PopUp_Setting.h"
#include "GameSystem/Enum/EnumConverter.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include <GameFramework/GameUserSettings.h>
#include <Internationalization/Internationalization.h>

#pragma region Interface

void UUI_ComboBox_Setting::InitOption(EOptionCategory Category, TArray<FOptionValuePair> Values)
{
	OptionCategory = Category;

	for (FOptionValuePair Value : Values)
	{
		GenerateItem<EOptionValue>(Value.Value, Value.Translation);
	}

	FSaveData_Setting Data = USaveManager::LoadData_Setting();
	EOptionValue Value = EOptionValue::None;
	switch (OptionCategory)
	{
	case EOptionCategory::Resolution:
		Value = Data.Resolution;
		break;

	case EOptionCategory::Grapic:
	{
		Value = Data.Grapic;

		UWidget* HideBox = GetWidgetFromName(TEXT("Image_HideBox"));
		ESlateVisibility SV = Value == EOptionValue::Custom ? ESlateVisibility::Collapsed : ESlateVisibility::Visible;
		HideBox->SetVisibility(SV);
		break;
	}
	case EOptionCategory::Language:
		Value = Data.Language;
		break;
	}

	ComboBox->SetSelectedOption(EnumConverter::GetEnumAsName(Value));
}

#pragma endregion

#pragma region ComboBox

void UUI_ComboBox_Setting::OnSelectionChanged(FName NameValue, ESelectInfo::Type EnumValue)
{
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

#pragma region Option

void UUI_ComboBox_Setting::SetOption_Resolution(FName OptionValue)
{
	UGameUserSettings* SettingHandle = UGameUserSettings::GetGameUserSettings();
	UEnum* EnumObj = StaticEnum<EOptionValue>();
	EOptionValue Value = static_cast<EOptionValue>(EnumObj->GetValueByName(OptionValue));

	auto* UI_Setting = GetTypedOuter<UUI_PopUp_Setting>();
	FSaveData_Setting& Data = UI_Setting->GetSettingData();
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

void UUI_ComboBox_Setting::SetOption_Grapic(FName OptionValue)
{
	UGameUserSettings* SettingHandle = UGameUserSettings::GetGameUserSettings();
	UEnum* EnumObj = StaticEnum<EOptionValue>();
	int64 Index = EnumObj->GetIndexByName(OptionValue);
	EOptionValue Value = static_cast<EOptionValue>(EnumObj->GetValueByName(OptionValue));

	auto* UI_Setting = GetTypedOuter<UUI_PopUp_Setting>();
	FSaveData_Setting& Data = UI_Setting->GetSettingData();
	Data.Grapic = Value;

	UWidget* HideBox = GetWidgetFromName(TEXT("Image_HideBox"));
	switch (Value)
	{
	case EOptionValue::Custom:
		HideBox->SetVisibility(ESlateVisibility::Collapsed);
		break;
		
	default:
		Data.AntiAliasing = Value;
		Data.Shadow = Value;
		Data.Texture = Value;
		Data.PostProcessing = Value;
		Data.Shading = Value;

		HideBox->SetVisibility(ESlateVisibility::Visible);
		SettingHandle->SetOverallScalabilityLevel(Index);
		break;
	}
}

void UUI_ComboBox_Setting::SetOption_Language(FName OptionValue)
{
	UEnum* EnumObj = StaticEnum<EOptionValue>();
	EOptionValue Value = static_cast<EOptionValue>(EnumObj->GetValueByName(OptionValue));

	auto* UI_Setting = GetTypedOuter<UUI_PopUp_Setting>();
	FSaveData_Setting& Data = UI_Setting->GetSettingData();
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