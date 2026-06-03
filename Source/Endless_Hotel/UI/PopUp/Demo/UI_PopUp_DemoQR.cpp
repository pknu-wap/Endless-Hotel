// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Demo/UI_PopUp_DemoQR.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include <Components/Button.h>

#pragma region Base

void UUI_PopUp_DemoQR::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Return->OnClicked.AddDynamic(this, &ThisClass::Click_Return);
}

#pragma endregion

#pragma region Button

void UUI_PopUp_DemoQR::Click_Return()
{
	auto* GameInstance = GetGameInstance<UEHGameInstance>();
	GameInstance->QuitGame();
}

#pragma endregion