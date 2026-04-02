// Copyright by 2026-1 WAP Game 2 team

#include "UI/Tutorial/UI_Tutorial.h"
#include "Components/TextBlock.h"

#pragma region Text

void UUI_Tutorial::SetTargetName(const FText& Name)
{
	Text_TargetName->SetText(Name);
}

#pragma endregion