// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/UI_Button_Base.h"

#pragma region Base

TSharedRef<SWidget> UUI_Button_Base::RebuildWidget()
{
	SetWidgetOwner();

	return Super::RebuildWidget();
}

#pragma endregion

#pragma region Owner

void UUI_Button_Base::SetWidgetOwner()
{
	Owner = GetTypedOuter<UUI_Base>();
}

#pragma endregion