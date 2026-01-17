// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/UI_Button_Base.h"

#pragma region Base

void UUI_Button_Base::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	SetWidgetOwner();
}

#pragma endregion

#pragma region Owner

void UUI_Button_Base::SetWidgetOwner()
{
	Owner = GetTypedOuter<UUI_Base>();
}

#pragma endregion

#pragma region Hightlight

void UUI_Button_Base::HighlightButton()
{
	FSlateBrush Brush;
	Brush.SetResourceObject(Texture_Highlight);
	WidgetStyle.SetNormal(Brush);
}

void UUI_Button_Base::UnhighlightButton()
{
	FSlateBrush Brush;
	Brush.SetResourceObject(Texture_Normal);
	WidgetStyle.SetNormal(Brush);
}

#pragma endregion