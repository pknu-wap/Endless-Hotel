// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Setting/UI_PopUp_Reset.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include <Components/Button.h>
#include <GameFramework/GameUserSettings.h>

#pragma region Base

void UUI_PopUp_Reset::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Yes->OnClicked.AddDynamic(this, &ThisClass::Click_Yes);
	Button_No->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
	Button_ESC->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
}

#pragma endregion

#pragma region Click

void UUI_PopUp_Reset::Click_Yes()
{
	switch (OptionCategory)
	{
	case EOptionCategory::Reset_Progression:
		USaveManager::DeleteData_Progression();
		break;

	case EOptionCategory::Reset_Setting:
		UGameUserSettings* SettingHandle = GEngine->GetGameUserSettings();
		SettingHandle->SetToDefaults();
		SettingHandle->ApplySettings(false);

		USaveManager::DeleteData_Setting();
		break;
	}

	Input_ESC();
}

#pragma endregion