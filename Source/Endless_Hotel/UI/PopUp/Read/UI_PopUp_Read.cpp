// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Read/UI_PopUp_Read.h"
#include "Actor/Interact/Read/InteractRead.h"

#pragma region Input

void UUI_PopUp_Read::Input_ESC()
{
	Cast<AInteractRead>(TargetObject)->PossessCamera(false);

	Super::Input_ESC();
}

#pragma endregion