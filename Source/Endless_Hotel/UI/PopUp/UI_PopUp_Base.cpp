﻿// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/UI_PopUp_Base.h"
#include "UI/Controller/UI_Controller.h"

#pragma region Base

FReply UUI_PopUp_Base::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return FReply::Handled();
}

FReply UUI_PopUp_Base::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	const FKey Key = InKeyEvent.GetKey();

	if (Key == EKeys::Enter)
	{
		Input_Enter();
		return FReply::Handled();
	}
	else if (Key == EKeys::Escape)
	{
		Input_ESC();
		return FReply::Handled();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

#pragma endregion

#pragma region Input

void UUI_PopUp_Base::Input_ESC()
{
	UUI_Controller* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->ClosePopUpWidget();
}

#pragma endregion