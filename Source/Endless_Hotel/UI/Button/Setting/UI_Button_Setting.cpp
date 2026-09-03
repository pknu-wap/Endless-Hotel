// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/Setting/UI_Button_Setting.h"
#include "UI/Controller/UI_Controller.h"
#include "Interface/UI/OptionInterface.h"
#include <Components/TextBlock.h>
#include <Components/HorizontalBox.h>
#include <Components/HorizontalBoxSlot.h>

#pragma region Option

void UUI_Button_Setting::InitOption(FOptionData OptionData)
{
	constexpr float Size = 447.f;
	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UUI_Base* ChildWidget = UICon->MakeChildWidget<UUI_Base, UHorizontalBox, UHorizontalBoxSlot>(HorizontalBox, OptionData.Class.LoadSynchronous(), ESlateSizeRule::Fill, Size);

	auto* Interface = Cast<IOptionInterface>(ChildWidget);
	Interface->InitOption(OptionData.Category, OptionData.Values);
	
	TextBlock->SetText(OptionData.Name);
}

#pragma endregion