// Copyright by 2026-1 WAP Game 2 team

#include "UI/Button/Setting/UI_Button_Category.h"
#include "UI/PopUp/Setting/UI_PopUp_Setting.h"

#pragma region Base

void UUI_Button_Category::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button->OnClicked.AddDynamic(this, &ThisClass::Click_Button);
}

#pragma endregion

#pragma region Category

void UUI_Button_Category::Click_Button()
{
	auto* UI_Setting = GetTypedOuter<UUI_PopUp_Setting>();
	UI_Setting->ShowOptionWidget(ButtonInfo.Category);
	UI_Setting->StartRotateGear(ButtonInfo.Angle);
}

#pragma endregion