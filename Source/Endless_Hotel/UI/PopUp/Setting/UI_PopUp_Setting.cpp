// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Setting/UI_PopUp_Setting.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/Slider/Custom/UI_Slider_Custom.h"
#include <GameFramework/GameUserSettings.h>
#include <Components/HorizontalBox.h>
#include <Components/Button.h>
#include <Components/Slider.h>
#include <Sound/SoundClass.h>

#pragma region Delegate

FSettingGrapic UUI_PopUp_Setting::SettingGrapic;
FSettingResolution UUI_PopUp_Setting::SettingResolution;
FSettingFrame UUI_PopUp_Setting::SettingFrame;
FSettingScreen UUI_PopUp_Setting::SettingScreen;
FSettingSensitivity UUI_PopUp_Setting::SettingSensitivity;

#pragma endregion

#pragma region Base

void UUI_PopUp_Setting::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SettingHandle = UGameUserSettings::GetGameUserSettings();

	SettingGrapic.AddDynamic(this, &ThisClass::Click_Grapic);
	SettingResolution.AddDynamic(this, &ThisClass::Click_Resolution);
	SettingFrame.AddDynamic(this, &ThisClass::Click_Frame);
	SettingScreen.AddDynamic(this, &ThisClass::Click_Screen);

	Slider_Sound->Slider_Main->OnValueChanged.AddDynamic(this, &ThisClass::Slide_Sound);
	Slider_Sensitivity->Slider_Main->OnValueChanged.AddDynamic(this, &ThisClass::Slide_Sensitivity);

	Button_Cancel->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
	Button_Apply->OnClicked.AddDynamic(this, &ThisClass::Click_Apply);

	Button_Reset->OnClicked.AddDynamic(this, &ThisClass::Click_Reset);
	Button_Language->OnClicked.AddDynamic(this, &ThisClass::Click_Language);
	Button_Brightness->OnClicked.AddDynamic(this, &ThisClass::Click_Brightness);

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

	HighlightButton(Buttons_Grapic, SettingData.Index_Grapic);
	HighlightButton(Buttons_Resolution, SettingData.Index_Resolution);
	HighlightButton(Buttons_Frame, SettingData.Index_Frame);
	HighlightButton(Buttons_Screen, SettingData.Index_Screen);

	Slider_Sound->Slider_Main->SetValue(SettingData.Value_Sound);
	Slider_Sensitivity->Slider_Main->SetValue(SettingData.Value_Sensitivity);
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

void UUI_PopUp_Setting::Click_Grapic(FButtonInfo Value)
{
	SettingData.Value_Grapic = Value.Value_Int;
	SettingData.Index_Grapic = Value.ButtonIndex;

	HighlightButton(Buttons_Grapic, Value.ButtonIndex);
}

void UUI_PopUp_Setting::Click_Resolution(FButtonInfo Value)
{
	SettingData.Value_Resolution = Value.Value_IntPoint;
	SettingData.Index_Resolution = Value.ButtonIndex;

	HighlightButton(Buttons_Resolution, Value.ButtonIndex);
}

void UUI_PopUp_Setting::Click_Frame(FButtonInfo Value)
{
	SettingData.Value_Frame = Value.Value_Float;
	SettingData.Index_Frame = Value.ButtonIndex;

	HighlightButton(Buttons_Frame, Value.ButtonIndex);
}

void UUI_PopUp_Setting::Click_Screen(FButtonInfo Value)
{
	SettingData.Value_Screen = Value.Value_WindowMode;
	SettingData.Index_Screen = Value.ButtonIndex;

	HighlightButton(Buttons_Screen, Value.ButtonIndex);
}

void UUI_PopUp_Setting::Slide_Sound(float Value)
{
	SettingData.Value_Sound = Value;
}

void UUI_PopUp_Setting::Slide_Sensitivity(float Value)
{
	SettingData.Value_Sensitivity = Value;
}

void UUI_PopUp_Setting::Click_Apply()
{
	SettingHandle->SetOverallScalabilityLevel(SettingData.Value_Grapic);
	SettingHandle->SetScreenResolution(SettingData.Value_Resolution);
	SettingHandle->SetFrameRateLimit(SettingData.Value_Frame);
	SettingHandle->SetFullscreenMode(static_cast<EWindowMode::Type>(SettingData.Value_Screen));

	SoundMaster->Properties.Volume = SettingData.Value_Sound;
	SettingSensitivity.Broadcast(SettingData.Value_Sensitivity);

	SettingHandle->ApplySettings(false);
	SettingHandle->SaveSettings();

	USaveManager::SaveSettingData(SettingData);

	Input_ESC();
}

void UUI_PopUp_Setting::Click_Reset()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(UI_Reset);
}

void UUI_PopUp_Setting::Click_Language()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(UI_Language);
}

void UUI_PopUp_Setting::Click_Brightness()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(UI_Brightness);
}

#pragma endregion