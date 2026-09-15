// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Setting/UI_PopUp_Option.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/Button/Setting/UI_Button_Setting.h"
#include <Components/VerticalBox.h>
#include <Components/VerticalBoxSlot.h>
#include <Components/TextBlock.h>

#pragma region Option

void UUI_PopUp_Option::InitOption(FOptionList List)
{
	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	for (FOptionData Data : List.List)
	{
		auto* ChildWidget = UICon->MakeChildWidget<UUI_Button_Setting, UVerticalBox, UVerticalBoxSlot>(VerticalBox, ButtonClass, ESlateSizeRule::Automatic);
		ChildWidget->InitOption(Data);
	}

	TextBlock->SetText(List.Name);
}

#pragma endregion