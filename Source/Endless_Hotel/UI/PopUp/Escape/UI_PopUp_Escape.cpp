// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Escape/UI_PopUp_Escape.h"
#include "UI/Controller/UI_Controller.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include <Components/Button.h>

#pragma region Base

void UUI_PopUp_Escape::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Resume->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
	Button_Setting->OnClicked.AddDynamic(this, &ThisClass::Click_Setting);
	Button_MainMenu->OnClicked.AddDynamic(this, &ThisClass::Click_MainMenu);
	Button_Quit->OnClicked.AddDynamic(this, &ThisClass::Click_Quit);
}

#pragma endregion

#pragma region Show

void UUI_PopUp_Escape::ShowWidget()
{
	Super::ShowWidget();

	auto* GameInstance = GetGameInstance<UEHGameInstance>();
	GameInstance->ActiveAdditionalDataLayer(EMapDataLayer::Lobby, true);
}

#pragma endregion

#pragma region Button

void UUI_PopUp_Escape::Click_Setting()
{
	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(EWidgetType::PopUp_Setting);
}

void UUI_PopUp_Escape::Click_MainMenu()
{
	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(EWidgetType::PopUp_MainMenuCheck);
}

void UUI_PopUp_Escape::Click_Quit()
{
	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(EWidgetType::PopUp_QuitCheck);
}

#pragma endregion