// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/Setting/UI_Button_Setting.h"
#include "Interface/UI/OptionInterface.h"
#include <Components/TextBlock.h>
#include <Components/HorizontalBox.h>
#include <Components/HorizontalBoxSlot.h>

#pragma region Option

void UUI_Button_Setting::InitOption(FOptionData OptionData)
{
	UUI_Base* AttachWidget = CreateWidget<UUI_Base>(this, OptionData.Class.LoadSynchronous());

	auto* Interface = Cast<IOptionInterface>(AttachWidget);
	Interface->InitOption(OptionData.Category, OptionData.Values);
	
	constexpr float Value = 447.f;
	FSlateChildSize Size = FSlateChildSize(ESlateSizeRule::Fill);
	Size.Value = Value;
	UHorizontalBoxSlot* HBSlot = HorizontalBox->AddChildToHorizontalBox(AttachWidget);
	HBSlot->SetSize(Size);

	TextBlock->SetText(OptionData.Name);
}

#pragma endregion