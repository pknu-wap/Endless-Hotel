// Copyright by 2025-2 WAP Game 2 team

#include "UI/CheckBox/Setting/UI_CheckBox_Setting.h"
#include "UI/PopUp/Setting/UI_PopUp_Setting.h"
#include "Sound/SoundController.h"
#include <Components/Image.h>

#pragma region Base

void UUI_CheckBox_Setting::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CheckBox->OnCheckStateChanged.AddDynamic(this, &ThisClass::Click_CheckBox);
}

#pragma endregion

#pragma region Interface

void UUI_CheckBox_Setting::InitOption(EOptionCategory Category, TArray<FOptionValuePair> Values)
{
	OptionCategory = Category;

	Click_CheckBox(Values[0].Value == EOptionValue::On);
}

#pragma endregion

#pragma region Click

void UUI_CheckBox_Setting::Click_CheckBox(bool bIsCheck)
{
	auto* UI_Setting = GetTypedOuter<UUI_PopUp_Setting>();
	FSaveData_Setting& Data = UI_Setting->GetSettingData();

	ESoundClassType Type = ESoundClassType::None;
	float Value = 0.f;

	switch (OptionCategory)
	{
	case EOptionCategory::Master:
		Type = ESoundClassType::Master;
		Value = bIsCheck ? Data.Master : Value;
		Data.EnableMaster = bIsCheck;
		break;

	case EOptionCategory::BGM:
		Type = ESoundClassType::BGM;
		Value = bIsCheck ? Data.BGM : Value;
		Data.EnableBGM = bIsCheck;
		break;

	case EOptionCategory::SFX:
		Type = ESoundClassType::SFX;
		Value = bIsCheck ? Data.SFX : Value;
		Data.EnableSFX = bIsCheck;
		break;

	case EOptionCategory::Voice:
		Type = ESoundClassType::Voice;
		Value = bIsCheck ? Data.Voice : Value;
		Data.EnableVoice = bIsCheck;
		break;

	case EOptionCategory::UI:
		Type = ESoundClassType::UI;
		Value = bIsCheck ? Data.UI : Value;
		Data.EnableUI = bIsCheck;
		break;
	}

	auto* SoundCon = GetGameInstance()->GetSubsystem<USoundController>();
	SoundCon->SetSoundClassValue(Type, Data.Master);

	ESlateVisibility SV = bIsCheck ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
	Image_Off->SetVisibility(SV);

	ECheckBoxState CS = bIsCheck ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
	CheckBox->SetCheckedState(CS);
}

#pragma endregion