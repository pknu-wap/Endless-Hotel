// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Default/UI_PopUp_Default.h"
#include "UI/Controller/UI_Controller.h"

#pragma region Input

void UUI_PopUp_Default::Input_ESC()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->CloseWidget();
}

#pragma endregion