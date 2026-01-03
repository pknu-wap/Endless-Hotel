// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Pause/Escape/UI_PopUp_QuitCheck.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "Components/Button.h"

#pragma region Base

void UUI_PopUp_QuitCheck::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Yes->OnClicked.AddDynamic(this, &ThisClass::Click_Yes);
	Button_No->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
}

#pragma endregion

#pragma region Click

void UUI_PopUp_QuitCheck::Click_Yes()
{
	UEHGameInstance* GameInstance = GetGameInstance<UEHGameInstance>();
	GameInstance->QuitGame();
}

#pragma endregion