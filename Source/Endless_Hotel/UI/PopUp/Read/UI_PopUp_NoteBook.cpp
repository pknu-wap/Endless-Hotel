// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Read/UI_PopUp_NoteBook.h"
#include "Actor/NoteBook/NoteBook.h"
#include <Components/Button.h>

#pragma region Base

void UUI_PopUp_NoteBook::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Left->OnClicked.AddDynamic(this, &ThisClass::Click_ButtonLeft);
	Button_Right->OnClicked.AddDynamic(this, &ThisClass::Click_ButtonRight);
}

#pragma endregion

#pragma region Click

void UUI_PopUp_NoteBook::Click_ButtonLeft()
{
	Cast<ANoteBook>(TargetObject)->TurnOverPage(true);
}

void UUI_PopUp_NoteBook::Click_ButtonRight()
{
	Cast<ANoteBook>(TargetObject)->TurnOverPage(false);
}

#pragma endregion