// Copyright by 2025-2 WAP Game 2 team

#include "UI/UI_Base.h"

#pragma region Base

void UUI_Base::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetIsFocusable(true);
}

void UUI_Base::NativeConstruct()
{
	Super::NativeConstruct();

	SetKeyboardFocus();
}

#pragma endregion