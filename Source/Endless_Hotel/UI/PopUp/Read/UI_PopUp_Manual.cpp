// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Read/UI_PopUp_Manual.h"
#include "Actor/Interact/Read/Manual/Manual.h"
#include <Components/Button.h>

#pragma region Base

void UUI_PopUp_Manual::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Left->OnClicked.AddDynamic(this, &ThisClass::Click_ButtonLeft);
	Button_Right->OnClicked.AddDynamic(this, &ThisClass::Click_ButtonRight);
}

#pragma endregion

#pragma region Click

void UUI_PopUp_Manual::Click_ButtonLeft()
{
	Cast<AManual>(TargetObject)->SwitchPaper();
}

void UUI_PopUp_Manual::Click_ButtonRight()
{
	Click_ButtonLeft();
}

#pragma endregion