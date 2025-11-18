// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/Main/UI_Button_Main.h"
#include "UI/Base/MainMenu/UI_MainMenu.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBoxSlot.h"

#pragma region Base

void UUI_Button_Main::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	OnHovered.Clear();
	OnHovered.AddDynamic(this, &ThisClass::OnButtonHover);
}

#pragma endregion

#pragma region Button

void UUI_Button_Main::ResetButton()
{
	SetButtonSize(ButtonSize_Normal);
	SetButtonTexture(Texture_Button_Normal);
	SetFontSize(FontSize_Normal);
}

void UUI_Button_Main::OnButtonHover()
{
	SetButtonSize(ButtonSize_Hover);
	SetButtonTexture(Texture_Button_Hover);
	SetFontSize(FontSize_Hover);

	Cast<UUI_MainMenu>(ButtonOwner)->ResetOtherButton(ButtonIndex);
}

void UUI_Button_Main::SetButtonSize(const float& ButtonSize)
{
	UVerticalBoxSlot* VBoxSlot = Cast<UVerticalBoxSlot>(Slot);
	FSlateChildSize TargetSize;
	TargetSize.Value = ButtonSize;
	VBoxSlot->SetSize(TargetSize);
}

void UUI_Button_Main::SetButtonTexture(UTexture2D* ButtonTexture)
{
	FSlateBrush Brush;
	Brush.SetResourceObject(ButtonTexture);
	WidgetStyle.SetNormal(Brush);
}

void UUI_Button_Main::SetFontSize(const uint8& FontSize)
{
	UTextBlock* TextBlock = Cast<UTextBlock>(GetChildAt(0));
	FSlateFontInfo FontInfo = TextBlock->Font;
	FontInfo.Size = FontSize * FontAdjustValue;
	TextBlock->SetFont(FontInfo);
}

#pragma endregion