// Copyright by 2026-1 WAP Game 2 team

#include "UI/Tutorial/UI_Tutorial.h"
#include <Components/TextBlock.h>

#pragma region Text

void UUI_Tutorial::SetTargetKey(const FText& Name)
{
	Text_Key->SetText(Name);
}

void UUI_Tutorial::SetTargetDescription(const FText& Name)
{
	Text_Description->SetText(Name);
}

#pragma endregion