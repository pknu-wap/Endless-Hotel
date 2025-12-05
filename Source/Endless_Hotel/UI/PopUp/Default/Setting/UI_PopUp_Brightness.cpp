// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Default/Setting/UI_PopUp_Brightness.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/Image.h"

#pragma region Base

FSettingBrightness UUI_PopUp_Brightness::SettingBrightness;

void UUI_PopUp_Brightness::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Apply->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Apply);

	Slider_Brightness->OnValueChanged.AddDynamic(this, &ThisClass::Slide_Brightness);
}

void UUI_PopUp_Brightness::NativeConstruct()
{
	Super::NativeConstruct();

	SettingData = USaveManager::LoadSettingData();
	Slider_Brightness->SetValue(SettingData.Value_Brightness);
}

#pragma endregion

#pragma region Button

void UUI_PopUp_Brightness::ButtonClick_Apply()
{
	USaveManager::SaveSettingData(SettingData);

	SettingBrightness.Broadcast();

	Input_ESC();
}

#pragma endregion

#pragma region Brightness

void UUI_PopUp_Brightness::Slide_Brightness(float Value)
{
	SettingData.Value_Brightness = Value;

	FLinearColor ColorValue = Image_Brightness->GetColorAndOpacity();
	ColorValue.A = Value * 0.9f + 0.1f;
	Image_Brightness->SetColorAndOpacity(ColorValue);
}

#pragma endregion