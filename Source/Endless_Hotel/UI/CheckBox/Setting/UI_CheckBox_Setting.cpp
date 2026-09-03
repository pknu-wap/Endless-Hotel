// Copyright by 2025-2 WAP Game 2 team

#include "UI/CheckBox/Setting/UI_CheckBox_Setting.h"
#include "UI/PopUp/Setting/UI_PopUp_Setting.h"
#include "Sound/SoundController.h"
#include "GameSystem/SaveGame/SaveManager.h"
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

	FSaveData_Setting Data = USaveManager::LoadData_Setting();
	uint8 Mute = 0;

	switch (Category)
	{
	case EOptionCategory::Master:
		Mute = Data.MuteMaster;
		break;

	case EOptionCategory::BGM:
		Mute = Data.MuteBGM;
		break;

	case EOptionCategory::SFX:
		Mute = Data.MuteSFX;
		break;

	case EOptionCategory::Voice:
		Mute = Data.MuteVoice;
		break;

	case EOptionCategory::UI:
		Mute = Data.MuteUI;
		break;
	}

	Click_CheckBox(Mute == 1);
}

#pragma endregion

#pragma region Click

void UUI_CheckBox_Setting::Click_CheckBox(bool bIsMute)
{
	auto* UI_Setting = GetTypedOuter<UUI_PopUp_Setting>();
	FSaveData_Setting& Data = UI_Setting->GetSettingData();

	ESoundClassType Type = ESoundClassType::None;
	float Value = 0.f;

	switch (OptionCategory)
	{
	case EOptionCategory::Master:
		Type = ESoundClassType::Master;
		Value = !bIsMute ? Data.Master : Value;
		Data.MuteMaster = bIsMute;
		break;

	case EOptionCategory::BGM:
		Type = ESoundClassType::BGM;
		Value = !bIsMute ? Data.BGM : Value;
		Data.MuteBGM = bIsMute;
		break;

	case EOptionCategory::SFX:
		Type = ESoundClassType::SFX;
		Value = !bIsMute ? Data.SFX : Value;
		Data.MuteSFX = bIsMute;
		break;

	case EOptionCategory::Voice:
		Type = ESoundClassType::Voice;
		Value = !bIsMute ? Data.Voice : Value;
		Data.MuteVoice = bIsMute;
		break;

	case EOptionCategory::UI:
		Type = ESoundClassType::UI;
		Value = !bIsMute ? Data.UI : Value;
		Data.MuteUI = bIsMute;
		break;
	}

	auto* SoundCon = GetGameInstance()->GetSubsystem<USoundController>();
	SoundCon->SetSoundClassValue(Type, Data.Master);

	ESlateVisibility SV = !bIsMute ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
	Image_Off->SetVisibility(SV);

	ECheckBoxState CS = bIsMute ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
	CheckBox->SetCheckedState(CS);
}

#pragma endregion