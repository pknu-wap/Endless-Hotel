// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Setting/UI_PopUp_SettingTutorial.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include <Components/Button.h>
#include <Components/CheckBox.h>

#pragma region Base

void UUI_PopUp_SettingTutorial::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CheckBox_Show->OnCheckStateChanged.AddDynamic(this, &ThisClass::Click_CheckBox);
	Button_YES->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
}

#pragma endregion

#pragma region Show

void UUI_PopUp_SettingTutorial::ShowWidget()
{
	Super::ShowWidget();

	FSaveData_Setting Data = USaveManager::LoadData_Setting();
	ECheckBoxState State = Data.bDontShowAgain ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
	CheckBox_Show->SetCheckedState(State);
}

#pragma endregion

#pragma region CheckBox

void UUI_PopUp_SettingTutorial::Click_CheckBox(bool bCheck)
{
	FSaveData_Setting Data = USaveManager::LoadData_Setting();
	Data.bDontShowAgain = bCheck;
	USaveManager::SaveData_Setting(Data);
}

#pragma endregion