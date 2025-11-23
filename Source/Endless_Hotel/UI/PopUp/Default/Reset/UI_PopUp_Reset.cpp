// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Default/Reset/UI_PopUp_Reset.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include "Components/Button.h"

#pragma region Base

void UUI_PopUp_Reset::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Yes->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Yes);
	Button_No->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
}

#pragma endregion

#pragma region Button

void UUI_PopUp_Reset::ButtonClick_Yes()
{
	USaveManager::DeleteCompendiumData();
	USaveManager::DeleteGameClearData();

	Input_ESC();
}

#pragma endregion