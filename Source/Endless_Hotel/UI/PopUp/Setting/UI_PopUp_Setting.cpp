// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Setting/UI_PopUp_Setting.h"
#include "UI/PopUp/Setting/UI_PopUp_Option.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include <Components/Button.h>
#include <Components/Border.h>
#include <Components/TextBlock.h>
#include <GameFramework/GameUserSettings.h>

#pragma region Declare

FSettingHighlight UUI_PopUp_Setting::Highlight;

#pragma endregion

#pragma region Base

void UUI_PopUp_Setting::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Normal->OnClicked.AddDynamic(this, &ThisClass::Click_Normal);
	Button_Input->OnClicked.AddDynamic(this, &ThisClass::Click_Input);

	Button_Apply->OnClicked.AddDynamic(this, &ThisClass::Click_Apply);
	Button_Cancel->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);

	Highlight.AddDynamic(this, &ThisClass::HighlightButtons);
}

void UUI_PopUp_Setting::NativeConstruct()
{
	Super::NativeConstruct();

	HighlightButtons();
}

void UUI_PopUp_Setting::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bRotateGear)
	{
		RotateGear(InDeltaTime);
	}
}

#pragma endregion

#pragma region Highlight

void UUI_PopUp_Setting::HighlightButtons()
{
	Data_Setting = USaveManager::LoadData_Setting();

	UI_Screen->HighlightOptions();
	UI_Grapic->HighlightOptions();
	UI_Sound->HighlightOptions();
	UI_Control_Normal->HighlightOptions();
	UI_Control_Input->HighlightOptions();
	UI_Gameplay->HighlightOptions();
	UI_System->HighlightOptions();

	Border_HideBox->SetVisibility(ESlateVisibility::Hidden);
}

#pragma endregion

#pragma region Category

void UUI_PopUp_Setting::SetCurrentCategoryText(FText Value)
{
	Text_CurrentCategory->SetText(Value);
}

#pragma endregion

#pragma region Option

void UUI_PopUp_Setting::ShowCategoryOption(ESettingCategory Target)
{
	UI_Screen->SetVisibility(ESlateVisibility::Hidden);
	UI_Grapic->SetVisibility(ESlateVisibility::Hidden);
	UI_Sound->SetVisibility(ESlateVisibility::Hidden);
	UI_Control_Normal->SetVisibility(ESlateVisibility::Hidden);
	UI_Control_Input->SetVisibility(ESlateVisibility::Hidden);
	UI_Gameplay->SetVisibility(ESlateVisibility::Hidden);
	UI_System->SetVisibility(ESlateVisibility::Hidden);

	Border_HideBox->SetVisibility(ESlateVisibility::Hidden);

	Button_Normal->SetVisibility(ESlateVisibility::Hidden);
	Button_Input->SetVisibility(ESlateVisibility::Hidden);
	
	switch (Target)
	{
	case ESettingCategory::Screen:
		UI_Screen->SetVisibility(ESlateVisibility::Visible);
		break;

	case ESettingCategory::Grapic:
	{
		UI_Grapic->SetVisibility(ESlateVisibility::Visible);
		if (Data_Setting.Grapic != EOptionValue::Custom)
		{
			Border_HideBox->SetVisibility(ESlateVisibility::Visible);
		}
		break;
	}

	case ESettingCategory::Sound:
		UI_Sound->SetVisibility(ESlateVisibility::Visible);
		break;

	case ESettingCategory::Control_Normal:
		UI_Control_Normal->SetVisibility(ESlateVisibility::Visible);
		Button_Normal->SetVisibility(ESlateVisibility::Visible);
		Button_Input->SetVisibility(ESlateVisibility::Visible);
		break;

	case ESettingCategory::Control_Input:
		UI_Control_Input->SetVisibility(ESlateVisibility::Visible);
		Button_Normal->SetVisibility(ESlateVisibility::Visible);
		Button_Input->SetVisibility(ESlateVisibility::Visible);
		break;

	case ESettingCategory::Gameplay:
		UI_Gameplay->SetVisibility(ESlateVisibility::Visible);
		break;

	case ESettingCategory::System:
		UI_System->SetVisibility(ESlateVisibility::Visible);
		break;
	}
}

void UUI_PopUp_Setting::SetHideBoxVisibility(ESlateVisibility Option)
{
	Border_HideBox->SetVisibility(Option);
}

void UUI_PopUp_Setting::Click_Normal()
{
	UI_Control_Normal->SetVisibility(ESlateVisibility::Visible);
	UI_Control_Input->SetVisibility(ESlateVisibility::Hidden);
}

void UUI_PopUp_Setting::Click_Input()
{
	UI_Control_Normal->SetVisibility(ESlateVisibility::Hidden);
	UI_Control_Input->SetVisibility(ESlateVisibility::Visible);
}

#pragma endregion

#pragma region Gear

void UUI_PopUp_Setting::StartRotateGear(float Target)
{
	if (Target == -1)
	{
		return;
	}

	TargetAngle = Target;
	bRotateGear = true;
}

void UUI_PopUp_Setting::RotateGear(float InDeltaTime)
{
	const float AddAngle = GetShortestAddAngle(CurrentAngle, TargetAngle);
	const float FinalAngle = CurrentAngle + AddAngle;
	const float RotateSpeed = 90.f;

	FWidgetTransform TargetTrans;
	CurrentAngle = FMath::FInterpConstantTo(CurrentAngle, FinalAngle, InDeltaTime, RotateSpeed);
	TargetTrans.Angle = CurrentAngle;

	UI_Gear->SetRenderTransform(TargetTrans);

	if (FMath::IsNearlyEqual(CurrentAngle, FinalAngle))
	{
		CurrentAngle = FinalAngle;
		TargetTrans.Angle = CurrentAngle;
		UI_Gear->SetRenderTransform(TargetTrans);

		bRotateGear = false;
	}
}

const float UUI_PopUp_Setting::GetShortestAddAngle(int32 Cur, int32 Tar)
{
	const float AngularSpacing = (Tar - Cur) % 360;

	if (AngularSpacing > 180)
	{
		return AngularSpacing - 360;
	}
	else if (AngularSpacing < -180)
	{
		return AngularSpacing + 360;
	}

	return AngularSpacing;
}

#pragma endregion

#pragma region Control

void UUI_PopUp_Setting::Click_Apply()
{
	auto* SettingHandle = UGameUserSettings::GetGameUserSettings();
	SettingHandle->SaveSettings();
	SettingHandle->ApplySettings(false);

	USaveManager::SaveData_Setting(Data_Setting);

	Input_ESC();
}

#pragma endregion