// Copyright by 2025-2 WAP Game 2 team

#include "UI/ComboBox/Setting/UI_ComboBox_Setting.h"
#include <Components/Border.h>

#pragma region Active

void UUI_ComboBox_Setting::ActiveComboBox()
{
	UBorder* Outline = Cast<UBorder>(GetParent());

	FSlateBrush& Brush = Outline->Background;
	Brush.DrawAs = ESlateBrushDrawType::RoundedBox;
	Brush.OutlineSettings.Color = OutlineColor_Focus;
	Brush.OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
	Outline->SetBrush(Brush);
}

void UUI_ComboBox_Setting::DeactiveComboBox(FName NameValue, ESelectInfo::Type EnumValue)
{
	UBorder* Outline = Cast<UBorder>(GetParent());

	FSlateBrush& Brush = Outline->Background;
	Brush.DrawAs = ESlateBrushDrawType::RoundedBox;
	Brush.OutlineSettings.Color = OutlineColor_Normal;
	Brush.OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
	Outline->SetBrush(Brush);
}

#pragma endregion