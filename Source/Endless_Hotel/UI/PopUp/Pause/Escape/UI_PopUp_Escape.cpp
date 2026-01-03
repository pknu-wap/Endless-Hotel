// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Pause/Escape/UI_PopUp_Escape.h"
#include "UI/Controller/UI_Controller.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "Components/Button.h"

#pragma region Base

void UUI_PopUp_Escape::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Resume->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
	Button_Setting->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Setting);
	Button_MainMenu->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_MainMenu);
	Button_Quit->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Quit);
}

#pragma endregion

#pragma region Button

void UUI_PopUp_Escape::ButtonClick_Setting()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(UI_Setting, EWidgetType::PopUp, EInputModeType::UIOnly);
}

void UUI_PopUp_Escape::ButtonClick_MainMenu()
{
	UEHGameInstance* GameInstance = GetGameInstance<UEHGameInstance>();
	GameInstance->OpenMap(EMapType::MainMenu);
}

void UUI_PopUp_Escape::ButtonClick_Quit()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(UI_QuitCheck, EWidgetType::PopUp, EInputModeType::UIOnly);
}

#pragma endregion