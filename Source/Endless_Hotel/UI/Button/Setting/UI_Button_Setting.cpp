// Copyright by 2025-2 WAP Game 2 team

#include "UI/Button/Setting/UI_Button_Setting.h"
#include "UI/PopUp/Setting/UI_PopUp_Setting.h"
#include "UI/Controller/UI_Controller.h"

#pragma region Base

void UUI_Button_Setting::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	OnClicked.Clear();
	OnClicked.AddDynamic(this, &ThisClass::Click_Button);
}

#pragma endregion

#pragma region Click

void UUI_Button_Setting::Click_Button()
{
	auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
	UICon->CloseWidget();
	UICon->OpenWidget(SettingInfo.Class);

	auto* SettingWidget = Cast<UUI_PopUp_Setting>(Owner);
	SettingWidget->SetCurrentCategoryText(SettingInfo.Name);
}

#pragma endregion