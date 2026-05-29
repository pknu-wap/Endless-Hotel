// Copyright by 2025-2 WAP Game 2 team

#include "UI/Base/Interact/UI_Interact.h"
#include <Components/TextBlock.h>
#include <Components/Image.h>

#pragma region Base

void UUI_Interact::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetVisibility(ESlateVisibility::Collapsed);
}

#pragma endregion

#pragma region Description

void UUI_Interact::SetDescription(FText Value)
{
	Text_Description->SetText(Value);
}

void UUI_Interact::ShowDescription(bool bIsShow)
{
	if (bIsShow)
	{
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Collapsed);
	}
}

#pragma endregion