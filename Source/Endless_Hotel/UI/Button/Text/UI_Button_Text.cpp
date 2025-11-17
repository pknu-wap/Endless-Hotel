// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/Text/UI_Button_Text.h"
#include "Components/TextBlock.h"

#pragma region Base

TSharedRef<SWidget, ESPMode::ThreadSafe> UUI_Button_Text::RebuildWidget()
{
	TSharedRef<SWidget, ESPMode::ThreadSafe> Btn = Super::RebuildWidget();

	OnPressed.RemoveDynamic(this, &ThisClass::OnButtonClicked);
	OnPressed.AddDynamic(this, &ThisClass::OnButtonClicked);

	OnHovered.RemoveDynamic(this, &ThisClass::OnButtonHovered);
	OnHovered.AddDynamic(this, &ThisClass::OnButtonHovered);

	OnUnhovered.RemoveDynamic(this, &ThisClass::OnButtonUnhovered);
	OnUnhovered.AddDynamic(this, &ThisClass::OnButtonUnhovered);

	return Btn;
}

#pragma endregion

#pragma region Button

void UUI_Button_Text::OnButtonClicked()
{
	for (auto* Child : GetAllChildren())
	{
		if (UTextBlock* TextBlock = Cast<UTextBlock>(Child))
		{
			TextBlock->SetColorAndOpacity(FLinearColor(0.6f, 0.6f, 0.6f, 1));
		}
	}
}

void UUI_Button_Text::OnButtonHovered()
{
	for (auto* Child : GetAllChildren())
	{
		if (UTextBlock* TextBlock = Cast<UTextBlock>(Child))
		{
			TextBlock->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
		}
	}
}

void UUI_Button_Text::OnButtonUnhovered()
{
	for (auto* Child : GetAllChildren())
	{
		if (UTextBlock* TextBlock = Cast<UTextBlock>(Child))
		{
			TextBlock->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 1));
		}
	}
}

#pragma endregion