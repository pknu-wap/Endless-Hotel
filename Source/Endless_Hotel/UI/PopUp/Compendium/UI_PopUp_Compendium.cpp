// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Compendium/UI_PopUp_Compendium.h"
#include "UI/Controller/UI_Controller.h"
#include <Components/Button.h>
#include <Components/VerticalBox.h>
#include <Components/HorizontalBox.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>

#pragma region Base

void UUI_PopUp_Compendium::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Previous->OnClicked.AddDynamic(this, &ThisClass::Click_Previous);
	Button_Next->OnClicked.AddDynamic(this, &ThisClass::Click_Next);
	Button_Close->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
}

#pragma endregion

#pragma region Button

void UUI_PopUp_Compendium::Click_Previous()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(UI_Previous);
}

void UUI_PopUp_Compendium::Click_Next()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->OpenWidget(UI_Next);
}

#pragma endregion