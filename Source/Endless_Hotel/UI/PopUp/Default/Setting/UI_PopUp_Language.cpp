// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Default/Setting/UI_PopUp_Language.h"
#include "Components/Button.h"

#pragma region Base

FSettingLanguage UUI_PopUp_Language::SettingLanguage;

void UUI_PopUp_Language::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SettingLanguage.AddDynamic(this, &ThisClass::ButtonClick_Language);
	Button_Apply->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Apply);
}

void UUI_PopUp_Language::NativeConstruct()
{
	Super::NativeConstruct();

	SettingData = USaveManager::LoadSettingData();
}

#pragma endregion

#pragma region Button

void UUI_PopUp_Language::ButtonClick_Language(FButtonInfo Value)
{
	SettingData.Value_Language = Value.Value_String;
	SettingData.Index_Language = Value.ButtonIndex;
}

void UUI_PopUp_Language::ButtonClick_Apply()
{
	FInternationalization::Get().SetCurrentCulture(SettingData.Value_Language);

	USaveManager::SaveSettingData(SettingData);
	
	Input_ESC();
}

#pragma endregion