// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/Text/UI_Button_Text.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBoxSlot.h"

#pragma region Base

UUI_Button_Text::UUI_Button_Text()
{
	OnPressed.RemoveDynamic(this, &ThisClass::OnButtonClicked);
	OnPressed.AddDynamic(this, &ThisClass::OnButtonClicked);

	OnHovered.RemoveDynamic(this, &ThisClass::OnButtonHovered);
	OnHovered.AddDynamic(this, &ThisClass::OnButtonHovered);

	HoverEvent.RemoveDynamic(this, &ThisClass::OnButtonUnhovered);
	HoverEvent.AddDynamic(this, &ThisClass::OnButtonUnhovered);
}

#pragma endregion

#pragma region Button

void UUI_Button_Text::OnButtonClicked()
{
	FLinearColor Text_Color = FColor::FromHex(TEXT("927F60FF")).ReinterpretAsLinear();
	for (auto* Child : GetAllChildren())
	{
		if (UTextBlock* TextBlock = Cast<UTextBlock>(Child))
		{
			TextBlock->SetColorAndOpacity(FSlateColor(Text_Color));
		}
	}
}

void UUI_Button_Text::OnButtonHovered()
{
	UVerticalBoxSlot* VBoxSlot = Cast<UVerticalBoxSlot>(Slot);
	VBoxSlot->Size.Value = ButtonSize_Hover;

	FSlateBrush Brush;
	Brush.SetResourceObject(Texture_Button_Hover);
	WidgetStyle.SetNormal(Brush);

	FLinearColor Text_Color = FColor::FromHex(TEXT("D2B78AFF")).ReinterpretAsLinear();
	for (auto* Child : GetAllChildren())
	{
		if (UTextBlock* TextBlock = Cast<UTextBlock>(Child))
		{
			TextBlock->SetColorAndOpacity(FSlateColor(Text_Color));

			FSlateFontInfo FontInfo = TextBlock->Font;
			FontInfo.Size = 96 * FontAdjustValue;
			TextBlock->SetFont(FontInfo);
		}
	}

	HoverEvent.Broadcast(ButtonIndex);
}

void UUI_Button_Text::OnButtonUnhovered(uint8 Index)
{
	if (ButtonIndex == Index)
	{
		return;
	}

	UVerticalBoxSlot* VBoxSlot = Cast<UVerticalBoxSlot>(Slot);
	VBoxSlot->Size.Value = ButtonSize_Normal;

	FSlateBrush Brush;
	Brush.SetResourceObject(Texture_Button_Normal);
	WidgetStyle.SetNormal(Brush);

	FLinearColor Text_Color = FColor::FromHex(TEXT("927F60FF")).ReinterpretAsLinear();
	for (auto* Child : GetAllChildren())
	{
		if (UTextBlock* TextBlock = Cast<UTextBlock>(Child))
		{
			TextBlock->SetColorAndOpacity(FSlateColor(Text_Color));

			FSlateFontInfo FontInfo = TextBlock->Font;
			FontInfo.Size = 64 * FontAdjustValue;
			TextBlock->SetFont(FontInfo);
		}
	}
}

#pragma endregion