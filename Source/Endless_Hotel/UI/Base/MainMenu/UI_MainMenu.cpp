// Copyright by 2025-2 WAP Game 2 team

#include "UI/Base/MainMenu/UI_MainMenu.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/PopUp/UI_PopUp_Base.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "Components/Button.h"

#pragma region Base

void UUI_MainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();

	Button_Start->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Start);
	Button_Compendium->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Compendium);
	Button_Setting->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Setting);
	Button_Quit->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Quit);
}

#pragma endregion

#pragma region Button

void UUI_MainMenu::ButtonClick_Start()
{
	UEHGameInstance* GameInstance = GetGameInstance<UEHGameInstance>();
	GameInstance->OpenMap(EMapType::Hotel);
}

void UUI_MainMenu::ButtonClick_Compendium()
{
	if (!UI_Compendium)
	{
		return;
	}

	UICon->OpenPopUpWidget(UI_Compendium);
}

void UUI_MainMenu::ButtonClick_Setting()
{
	if (!UI_Setting)
	{
		return;
	}

	UICon->OpenPopUpWidget(UI_Setting);
}

void UUI_MainMenu::ButtonClick_Quit()
{
	UEHGameInstance* GameInstance = GetGameInstance<UEHGameInstance>();
	GameInstance->QuitGame();
}

#pragma endregion