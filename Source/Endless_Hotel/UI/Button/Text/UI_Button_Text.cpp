// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/Text/UI_Button_Text.h"
#include "Components/TextBlock.h"

#pragma region Base

UUI_Button_Text::UUI_Button_Text(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	OnHovered.AddDynamic(this, &ThisClass::ButtonHover);
	OnUnhovered.AddDynamic(this, &ThisClass::ButtonUnhover);
}

#pragma endregion

#pragma region Button

void UUI_Button_Text::ButtonHover()
{
	UTextBlock* ButtonText = Cast<UTextBlock>(GetChildAt(0));
	FLinearColor Text_Color = FColor::FromHex(Color_Hover).ReinterpretAsLinear();
	ButtonText->SetColorAndOpacity(FSlateColor(Text_Color));
}

void UUI_Button_Text::ButtonUnhover()
{
	UTextBlock* ButtonText = Cast<UTextBlock>(GetChildAt(0));
	FLinearColor Text_Color = FColor::FromHex(Color_Unhover).ReinterpretAsLinear();
	ButtonText->SetColorAndOpacity(FSlateColor(Text_Color));
}

#pragma endregion