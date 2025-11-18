// Copyright by 2025-2 WAP Game 2 team

#include "UI/Base/MainMenu/UI_MainMenu.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/PopUp/UI_PopUp_Base.h"
#include "UI/Button/Main/UI_Button_Main.h"
#include "GameSystem/GameInstance/EHGameInstance.h"
#include "Components/VerticalBox.h"

#pragma region Base

void UUI_MainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Buttons.Add(Cast<UButton>(VBox_Buttons->GetChildAt(Index_Start)));
	Buttons.Add(Cast<UButton>(VBox_Buttons->GetChildAt(Index_Setting)));
	Buttons.Add(Cast<UButton>(VBox_Buttons->GetChildAt(Index_Quit)));

	Cast<UUI_Button_Base>(Buttons[Index_Start])->SetButtonOwner(this);
	Cast<UUI_Button_Base>(Buttons[Index_Setting])->SetButtonOwner(this);
	Cast<UUI_Button_Base>(Buttons[Index_Quit])->SetButtonOwner(this);

	Buttons[Index_Start]->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Start);
	Buttons[Index_Setting]->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Setting);
	Buttons[Index_Quit]->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Quit);

	Button_Compendium->OnClicked.AddDynamic(this, &ThisClass::ButtonClick_Compendium);
}

#pragma endregion

#pragma region Click

void UUI_MainMenu::ButtonClick_Start()
{
	UEHGameInstance* GameInstance = GetGameInstance<UEHGameInstance>();
	GameInstance->OpenMap(EMapType::Hotel);
}

void UUI_MainMenu::ButtonClick_Compendium()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenPopUpWidget(UI_Compendium);
}

void UUI_MainMenu::ButtonClick_Setting()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenPopUpWidget(UI_Setting);
}

void UUI_MainMenu::ButtonClick_Quit()
{
	UEHGameInstance* GameInstance = GetGameInstance<UEHGameInstance>();
	GameInstance->QuitGame();
}

#pragma endregion

#pragma region Reset

void UUI_MainMenu::ResetOtherButton(const uint8& CurrentIndex)
{
	for (UButton* Btn : Buttons)
	{
		auto* Button = Cast<UUI_Button_Main>(Btn);

		if (Button->GetButtonIndex() == CurrentIndex)
		{
			continue;
		}

		Button->ResetButton();
	}
}

#pragma endregion