// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Setting/UI_PopUp_WrongCheck.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include <Components/Button.h>

#pragma region Base

void UUI_PopUp_WrongCheck::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Yes->OnClicked.AddDynamic(this, &ThisClass::Click_Yes);
	Button_No->OnClicked.AddDynamic(this, &ThisClass::Click_No);
	Button_ESC->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
}

#pragma endregion

#pragma region Click

void UUI_PopUp_WrongCheck::Click_Yes()
{
	FSaveData_Setting Data = USaveManager::LoadData_Setting();
	Data.WrongCheck = EOptionValue::On;
	USaveManager::SaveData_Setting(Data);

	Input_ESC();
}

void UUI_PopUp_WrongCheck::Click_No()
{
	FSaveData_Setting Data = USaveManager::LoadData_Setting();
	Data.WrongCheck = EOptionValue::Off;
	USaveManager::SaveData_Setting(Data);

	Input_ESC();
}

#pragma endregion