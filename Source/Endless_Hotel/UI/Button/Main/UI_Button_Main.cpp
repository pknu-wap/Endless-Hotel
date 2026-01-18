// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/Main/UI_Button_Main.h"
#include "UI/HUD/Title/UI_HUD_Title.h"

#pragma region Base

void UUI_Button_Main::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	OnHovered.Clear();
	OnHovered.AddDynamic(this, &ThisClass::Hover_Button);

	OnUnhovered.Clear();
	OnUnhovered.AddDynamic(this, &ThisClass::Unhover_Button);
}

#pragma endregion

#pragma region Hover

void UUI_Button_Main::Hover_Button()
{
	Cast<UUI_HUD_Title>(Owner)->PlayButtonAnim_Hover(ButtonType);
}

void UUI_Button_Main::Unhover_Button()
{
	Cast<UUI_HUD_Title>(Owner)->PlayButtonAnim_Unhover(ButtonType);
}

#pragma endregion