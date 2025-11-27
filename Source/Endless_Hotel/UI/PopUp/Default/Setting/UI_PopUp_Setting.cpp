// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Default/Setting/UI_PopUp_Setting.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/Button/Setting/UI_Button_Setting.h"
#include "GameFramework/GameUserSettings.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"
#include "Sound/SoundClass.h"

#pragma region Delegate

FSettingGrapic UUI_PopUp_Setting::SettingGrapic;
FSettingResolution UUI_PopUp_Setting::SettingResolution;
FSettingFrame UUI_PopUp_Setting::SettingFrame;
FSettingScreen UUI_PopUp_Setting::SettingScreen;

// 해당 기능은 최종 이후에 추가 예정
//FSettingLanguage UUI_PopUp_Setting::SettingLanguage;

#pragma endregion

#pragma region Base

void UUI_PopUp_Setting::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SettingHandle = UGameUserSettings::GetGameUserSettings();

	SettingGrapic.AddDynamic(this, &ThisClass::ButtonClick_Grapic);
	SettingResolution.AddDynamic(this, &ThisClass::ButtonClick_Resolution);
	SettingFrame.AddDynamic(this, &ThisClass::ButtonClick_Resolution);
	SettingScreen.AddDynamic(this, &ThisClass::ButtonClick_Screen);

	// 해당 기능은 최종 이후에 추가 예정
	//SettingLanguage.AddDynamic(this, &ThisClass::ButtonClick_Language);

	Button_Cancel->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
	Button_Apply->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Apply);
	Button_Reset->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Reset);

	SettingButtonOwner(Buttons_Grapic);
	SettingButtonOwner(Buttons_Resolution);
	SettingButtonOwner(Buttons_Frame);
	SettingButtonOwner(Buttons_Screen);
}

void UUI_PopUp_Setting::NativeConstruct()
{
	Super::NativeConstruct();
	
	FSettingSaveData SaveData = USaveManager::LoadSettingData();

	Value_Grapic = SaveData.Grapic;
	Value_Resolution = SaveData.Resolution;
	Value_Screen = static_cast<EWindowMode::Type>(SaveData.Screen);
	Value_Sound = SaveData.Sound;

	//Value_Language = SaveData.Language;
}

#pragma endregion

#pragma region Setting

void UUI_PopUp_Setting::SettingButtonOwner(UHorizontalBox* ButtonBox)
{
	for (auto* Button : ButtonBox->GetAllChildren())
	{
		auto* Target = Cast<UUI_Button_Base>(Button);
		Target->SetButtonOwner(this);
	}
}

#pragma endregion

#pragma region Button

void UUI_PopUp_Setting::ButtonClick_Grapic(FButtonInfo Value)
{
	Value_Grapic = Value.Value_Int;
}

void UUI_PopUp_Setting::ButtonClick_Resolution(FButtonInfo Value)
{
	Value_Resolution = Value.Value_IntPoint;
}

void UUI_PopUp_Setting::ButtonClick_Frame(FButtonInfo Value)
{
	Value_Frame = Value.Value_Float;
}

void UUI_PopUp_Setting::ButtonClick_Screen(FButtonInfo Value)
{
	Value_Screen = Value.Value_WindowMode;
}

void UUI_PopUp_Setting::SliderClick_Sound(FButtonInfo Value)
{
	Value_Sound = Value.Value_Float;
}

// 해당 기능은 최종 이후 추가 예정
//void UUI_PopUp_Setting::SliderClick_Brightness(FButtonInfo Value)
//{
//
//}
//
//void UUI_PopUp_Setting::ButtonClick_Language(FString Value)
//{
//	Value_Language = Value;
//}

void UUI_PopUp_Setting::ButtonClick_Apply()
{
	SettingHandle->SetOverallScalabilityLevel(Value_Grapic);
	SettingHandle->SetScreenResolution(Value_Resolution);
	SettingHandle->SetFullscreenMode(Value_Screen);
	SoundMaster->Properties.Volume = Value_Sound;

	//FInternationalization::Get().SetCurrentCulture(Value_Language);

	SettingHandle->ApplySettings(false);
	SettingHandle->SaveSettings();

	FSettingSaveData SaveData;

	SaveData.Grapic = Value_Grapic;
	SaveData.Resolution = Value_Resolution;
	SaveData.Screen = Value_Screen;
	SaveData.Sound = Value_Sound;

	//SaveData.Language = Value_Language;

	USaveManager::SaveSettingData(SaveData);

	Input_ESC();
}

void UUI_PopUp_Setting::ButtonClick_Reset()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(UI_Reset, EWidgetType::PopUp, EInputModeType::UIOnly);
}

#pragma endregion

#pragma region Highlight

void UUI_PopUp_Setting::HighlightButton(const ESettingCategory& ButtonType, const uint8& TargetIndex)
{
	UHorizontalBox* SearchBox = nullptr;

	switch (ButtonType)
	{
	case ESettingCategory::Grapic:
		SearchBox = Buttons_Grapic;
		break;

	case ESettingCategory::Resolution:
		SearchBox = Buttons_Resolution;
		break;

	case ESettingCategory::Frame:
		SearchBox = Buttons_Frame;
		break;

	case ESettingCategory::Screen:
		SearchBox = Buttons_Screen;
		break;
	}

	for (auto* SearchTarget : SearchBox->GetAllChildren())
	{
		auto* Target = Cast<UUI_Button_Setting>(SearchTarget);

		if (Target->GetButtonIndex() == TargetIndex)
		{
			Target->HighlightButton();
			continue;
		}

		Target->UnhighlightButton();
	}
}

#pragma endregion