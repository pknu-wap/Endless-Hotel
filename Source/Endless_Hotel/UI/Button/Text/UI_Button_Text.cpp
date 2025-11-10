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
	FLinearColor Click_Color = FColor::FromHex(TEXT("927F60FF")).ReinterpretAsLinear();

	for (auto* Child : GetAllChildren())
	{
		if (UTextBlock* TextBlock = Cast<UTextBlock>(Child))
		{
			TextBlock->SetColorAndOpacity(FSlateColor(Click_Color));
		}
	}
}

void UUI_Button_Text::OnButtonHovered()
{
	FLinearColor Hover_Color = FColor::FromHex(TEXT("D2B78AFF")).ReinterpretAsLinear();

	for (auto* Child : GetAllChildren())
	{
		if (UTextBlock* TextBlock = Cast<UTextBlock>(Child))
		{
			TextBlock->SetColorAndOpacity(FSlateColor(Hover_Color));

			FSlateFontInfo FontInfo = TextBlock->Font;
			FontInfo.Size = 96 * FontAdjustValue;
			TextBlock->SetFont(FontInfo);
		}
	}
}

void UUI_Button_Text::OnButtonUnhovered()
{
	FLinearColor Unhover_Color = FColor::FromHex(TEXT("927F60FF")).ReinterpretAsLinear();

	for (auto* Child : GetAllChildren())
	{
		if (UTextBlock* TextBlock = Cast<UTextBlock>(Child))
		{
			TextBlock->SetColorAndOpacity(FSlateColor(Unhover_Color));

			FSlateFontInfo FontInfo = TextBlock->Font;
			FontInfo.Size = 64 * FontAdjustValue;
			TextBlock->SetFont(FontInfo);
		}
	}
}

#pragma endregion