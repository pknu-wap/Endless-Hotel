// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/UI_Button_Base.h"

#pragma region Base

TSharedRef<SWidget> UUI_Button_Base::RebuildWidget()
{
	Owner = GetTypedOuter<UUI_Base>();

	return Super::RebuildWidget();
}

#pragma endregion