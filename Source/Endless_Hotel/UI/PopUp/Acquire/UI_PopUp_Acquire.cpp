// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Acquire/UI_PopUp_Acquire.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>

#pragma region Base

void UUI_PopUp_Acquire::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_ESC->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
}

#pragma endregion

#pragma region Input

void UUI_PopUp_Acquire::Input_ESC()
{
	Item->Destroy();

	Super::Input_ESC();
}

#pragma endregion

#pragma region Info

void UUI_PopUp_Acquire::SetInfoText(FText Info)
{
	Text_Info->SetText(Info);
}

#pragma endregion