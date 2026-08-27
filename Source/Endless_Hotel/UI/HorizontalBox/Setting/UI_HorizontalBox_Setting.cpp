// Copyright by 2026-1 WAP Game 2 team

#include "UI/HorizontalBox/Setting/UI_HorizontalBox_Setting.h"
#include "UI/Button/Setting/UI_Button_Option.h"
#include <Components/Button.h>

#pragma region Interface

void UUI_HorizontalBox_Setting::InitOption(EOptionCategory Category, TArray<FOptionValuePair> Values)
{
	for (FOptionValuePair Value : Values)
	{
		UUI_Button_Option* AttachButton = CreateWidget<UUI_Button_Option>(this, ButtonClass);
		AttachButton->SetOptionInfo(Category, Value);
		Buttons.Add(AttachButton);

		constexpr float SizeValue = 1.f;
		FSlateChildSize Size = FSlateChildSize(ESlateSizeRule::Fill);
		Size.Value = SizeValue;
		UHorizontalBoxSlot* HBSlot = HorizontalBox->AddChildToHorizontalBox(AttachButton);
		HBSlot->SetSize(Size);
	}
}

#pragma endregion

#pragma region Highlight

void UUI_HorizontalBox_Setting::Highlight(EOptionValue TargetValue)
{
	for (UUI_Button_Option* Button : Buttons)
	{
		UButton* Btn = Button->GetButton();
		FButtonStyle ButtonStyle = Btn->GetStyle();
		ButtonStyle.Normal.TintColor = Color_Default;
		if (Button->GetValue() == TargetValue)
		{
			ButtonStyle.Normal.TintColor = Color_Highlight;
		}
		Btn->SetStyle(ButtonStyle);
	}
}

#pragma endregion