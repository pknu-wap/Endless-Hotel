// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Pause/Demo/UI_PopUp_Demo.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "Components/Button.h"

#pragma region Base

void UUI_PopUp_Demo::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Return->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Return);
}

#pragma endregion

#pragma region Button

void UUI_PopUp_Demo::ButtonClick_Return()
{
	UEHGameInstance* GameInstance = GetGameInstance<UEHGameInstance>();
	GameInstance->OpenMap(EMapType::MainMenu);
}

#pragma endregion