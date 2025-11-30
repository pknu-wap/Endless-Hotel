// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Default/Setting/UI_PopUp_Brightness.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/Image.h"

#pragma region Base

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
	Slider_Brightness->Value = SettingData.Value_Brightness;
	Value_Brightness = SettingData.Value_Brightness;
}

#pragma endregion

#pragma region Button

void UUI_PopUp_Brightness::ButtonClick_Apply()
{
	SettingData = USaveManager::LoadSettingData();
	SettingData.Value_Brightness = Value_Brightness;
	USaveManager::SaveSettingData(SettingData);

	Input_ESC();
}

#pragma endregion

#pragma region Brightness

void UUI_PopUp_Brightness::Slide_Brightness(float Value)
{
	Value_Brightness = 1 - Value;

	FLinearColor ColorValue = Image_Brightness->GetColorAndOpacity();
	ColorValue.A = Value;
	Image_Brightness->SetColorAndOpacity(ColorValue);
}

#pragma endregion