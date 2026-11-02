// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Interact/UI_PopUp_InteractTutorial.h"
#include <Components/Button.h>

#pragma region Base

void UUI_PopUp_InteractTutorial::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_YES->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
}

#pragma endregion