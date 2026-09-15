// Copyright by 2026-1 WAP Game 2 team

#include "UI/PopUp/Read/UI_PopUp_Read.h"
#include "Actor/Interact/Read/InteractRead.h"
#include <Components/Button.h>

#pragma region Base

void UUI_PopUp_Read::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_ESC->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
}

#pragma endregion

#pragma region Input

void UUI_PopUp_Read::Input_ESC()
{
	auto* ReadObject = Cast<AInteractRead>(TargetObject);
	ReadObject->PossessCamera(false);

	Super::Input_ESC();
}

#pragma endregion