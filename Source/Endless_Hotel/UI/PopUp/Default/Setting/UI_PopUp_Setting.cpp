// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Default/Setting/UI_PopUp_Setting.h"
#include "UI/Controller/UI_Controller.h"
#include "GameFramework/GameUserSettings.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Sound/SoundClass.h"

#pragma region Delegate

FSettingGrapic UUI_PopUp_Setting::SettingGrapic;
FSettingResolution UUI_PopUp_Setting::SettingResolution;
FSettingFrame UUI_PopUp_Setting::SettingFrame;
FSettingScreen UUI_PopUp_Setting::SettingScreen;

#pragma endregion

#pragma region Base

void UUI_PopUp_Setting::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SettingHandle = UGameUserSettings::GetGameUserSettings();

	SettingGrapic.AddDynamic(this, &ThisClass::ButtonClick_Grapic);
	SettingResolution.AddDynamic(this, &ThisClass::ButtonClick_Resolution);
	SettingFrame.AddDynamic(this, &ThisClass::ButtonClick_Frame);
	SettingScreen.AddDynamic(this, &ThisClass::ButtonClick_Screen);

	Slider_Sound->OnValueChanged.AddDynamic(this, &ThisClass::Slide_Sound);

	Button_Cancel->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
	Button_Apply->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Apply);

	Button_Reset->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Reset);
	Button_Brightness->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Brightness);

	SettingButtonOwner(Buttons_Grapic);
	SettingButtonOwner(Buttons_Resolution);
	SettingButtonOwner(Buttons_Frame);
	SettingButtonOwner(Buttons_Screen);
}

void UUI_PopUp_Setting::NativeConstruct()
{
	Super::NativeConstruct();
	
	LoadSettingData();
}

#pragma endregion

#pragma region Data

void UUI_PopUp_Setting::LoadSettingData()
{
	SettingData = USaveManager::LoadSettingData();

	HighlightButton(ESettingCategory::Grapic, SettingData.Index_Grapic);
	HighlightButton(ESettingCategory::Resolution, SettingData.Index_Resolution);
	HighlightButton(ESettingCategory::Frame, SettingData.Index_Frame);
	HighlightButton(ESettingCategory::Screen, SettingData.Index_Screen);

	Slider_Sound->SetValue(SettingData.Value_Sound);
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
	SettingData.Value_Grapic = Value.Value_Int;
	SettingData.Index_Grapic = Value.ButtonIndex;
}

void UUI_PopUp_Setting::ButtonClick_Resolution(FButtonInfo Value)
{
	SettingData.Value_Resolution = Value.Value_IntPoint;
	SettingData.Index_Resolution = Value.ButtonIndex;
}

void UUI_PopUp_Setting::ButtonClick_Frame(FButtonInfo Value)
{
	SettingData.Value_Frame = Value.Value_Float;
	SettingData.Index_Frame = Value.ButtonIndex;
}

void UUI_PopUp_Setting::ButtonClick_Screen(FButtonInfo Value)
{
	SettingData.Value_Screen = Value.Value_WindowMode;
	SettingData.Index_Screen = Value.ButtonIndex;
}

void UUI_PopUp_Setting::Slide_Sound(float Value)
{
	SettingData.Value_Sound = Value;
}

void UUI_PopUp_Setting::ButtonClick_Apply()
{
	SettingHandle->SetOverallScalabilityLevel(SettingData.Value_Grapic);
	SettingHandle->SetScreenResolution(SettingData.Value_Resolution);
	SettingHandle->SetFullscreenMode(static_cast<EWindowMode::Type>(SettingData.Value_Screen));
	SoundMaster->Properties.Volume = SettingData.Value_Sound;

	//FInternationalization::Get().SetCurrentCulture(Value_Language);

	SettingHandle->ApplySettings(false);
	SettingHandle->SaveSettings();

	USaveManager::SaveSettingData(SettingData);

	Input_ESC();
}

void UUI_PopUp_Setting::ButtonClick_Reset()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(UI_Reset, EWidgetType::PopUp, EInputModeType::UIOnly);
}

void UUI_PopUp_Setting::ButtonClick_Brightness()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(UI_Brightness, EWidgetType::PopUp, EInputModeType::UIOnly);
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