// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Setting/UI_PopUp_Language.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include <Components/Button.h>
#include <Components/ScrollBox.h>
#include <Components/TextBlock.h>

#pragma region Base

FSettingLanguage UUI_PopUp_Language::SettingLanguage;

void UUI_PopUp_Language::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Buttons_Language->SetAlwaysShowScrollbar(true);

	SettingLanguage.AddDynamic(this, &ThisClass::Click_Language);
	Button_Apply->OnClicked.AddDynamic(this, &ThisClass::Click_Apply);
}

void UUI_PopUp_Language::NativeConstruct()
{
	Super::NativeConstruct();

	LoadSettingData();
}

#pragma endregion

#pragma region Data

void UUI_PopUp_Language::LoadSettingData()
{
	SettingData = USaveManager::LoadSettingData();

	HighlightButton(Buttons_Language, SettingData.Index_Language);

	Text_Current->SetText(FText::FromString(SettingData.Value_Language));
}

#pragma endregion

#pragma region Button

void UUI_PopUp_Language::Click_Language(FButtonInfo Value)
{
	SettingData.Value_Language = Value.Value_String;
	SettingData.Index_Language = Value.ButtonIndex;

	HighlightButton(Buttons_Language, SettingData.Index_Language);

	Text_Current->SetText(FText::FromString(Value.Value_String));
}

void UUI_PopUp_Language::Click_Apply()
{
	FInternationalization::Get().SetCurrentCulture(SettingData.Value_Language);

	USaveManager::SaveSettingData(SettingData);
	
	Input_ESC();
}

#pragma endregion