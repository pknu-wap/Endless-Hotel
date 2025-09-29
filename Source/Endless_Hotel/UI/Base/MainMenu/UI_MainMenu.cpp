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

	StartButton->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Start);
	DictionaryButton->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Dictionary);
	SettingButton->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Setting);
	QuitButton->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Quit);
}

#pragma endregion

#pragma region Buttons

void UUI_MainMenu::ButtonClick_Start()
{
	UEHGameInstance* GameInstance = GetGameInstance<UEHGameInstance>();
	GameInstance->OpenMap(EMapType::Hotel);
}

void UUI_MainMenu::ButtonClick_Dictionary()
{
	if (!UI_Dictionary)
	{
		return;
	}

	UICon->OpenPopUpWidget(UI_Dictionary);
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