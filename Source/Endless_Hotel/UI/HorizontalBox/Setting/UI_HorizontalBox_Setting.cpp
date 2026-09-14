// Copyright by 2026-1 WAP Game 2 team

#include "UI/HorizontalBox/Setting/UI_HorizontalBox_Setting.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/Button/Setting/UI_Button_Option.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include <Components/Button.h>

#pragma region Interface

void UUI_HorizontalBox_Setting::InitOption(EOptionCategory Category, TArray<FOptionValuePair> Values)
{
	SettingCategory = Category;

	for (FOptionValuePair Value : Values)
	{
		auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
		UUI_Button_Option* ChildWidget = UICon->MakeChildWidget<UUI_Button_Option, UHorizontalBox, UHorizontalBoxSlot>(HorizontalBox, ButtonClass);
		ChildWidget->SetOptionInfo(SettingCategory, Value);
		Buttons.Add(ChildWidget);
	}

	FSaveData_Setting Data = USaveManager::LoadData_Setting();
	EOptionValue Value = EOptionValue::None;
	switch (SettingCategory)
	{
	case EOptionCategory::Window:
		Value = Data.Window;
		break;

	case EOptionCategory::Aspect:
		Value = Data.Aspect;
		break;

	case EOptionCategory::Frame:
		Value = Data.Frame;
		break;

	case EOptionCategory::VSync:
		Value = Data.VSync;
		break;

	case EOptionCategory::HDR:
		Value = Data.HDR;
		break;

	case EOptionCategory::AntiAliasing:
		Value = Data.AntiAliasing;
		break;

	case EOptionCategory::Shadow:
		Value = Data.Shadow;
		break;

	case EOptionCategory::Texture:
		Value = Data.Texture;
		break;

	case EOptionCategory::PostProcessing:
		Value = Data.PostProcessing;
		break;

	case EOptionCategory::Shading:
		Value = Data.Shading;
		break;

	case EOptionCategory::Overlap:
		Value = Data.Overlap;
		break;

	case EOptionCategory::CameraShake:
		Value = Data.CameraShake;
		break;

	case EOptionCategory::WrongCheck:
		Value = Data.WrongCheck;
		break;
	}

	Highlight(Value);
}

#pragma endregion

#pragma region Show

void UUI_HorizontalBox_Setting::ShowWidget()
{
	Super::ShowWidget();

	if (SettingCategory != EOptionCategory::Overlap)
	{
		return;
	}

	UWidget* HideBox = GetWidgetFromName(TEXT("Image_HideBox"));
	ESlateVisibility SV = USaveManager::LoadData_Progression().bGameClear ? ESlateVisibility::Collapsed : ESlateVisibility::Visible;
	HideBox->SetVisibility(SV);
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