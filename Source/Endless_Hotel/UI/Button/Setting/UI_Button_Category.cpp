// Copyright by 2026-1 WAP Game 2 team

#include "UI/Button/Setting/UI_Button_Category.h"
#include "UI/PopUp/Setting/UI_PopUp_Setting.h"
#include "UI/Controller/UI_Controller.h"

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
	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	auto* UI_Setting = Cast<UUI_PopUp_Setting>((UICon->GetCachedWidget(EWidgetType::PopUp_Setting)));
	UI_Setting->CurrentCategory = ButtonInfo.Category;
	UI_Setting->ShowCurrentCategoryWidget();
	UI_Setting->StartRotateGear(ButtonInfo.Angle);
}

#pragma endregion