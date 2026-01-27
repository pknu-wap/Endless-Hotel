// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Setting/UI_PopUp_Setting.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <GameFramework/GameUserSettings.h>

#pragma region Base

void UUI_PopUp_Setting::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Apply->OnClicked.AddDynamic(this, &ThisClass::Click_Apply);
	Button_Cancel->OnClicked.AddDynamic(this, &ThisClass::Input_ESC);
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
	/*UI_Sound->SetVisibility(ESlateVisibility::Hidden);
	UI_Control->SetVisibility(ESlateVisibility::Hidden);
	UI_Gameplay->SetVisibility(ESlateVisibility::Hidden);
	UI_System->SetVisibility(ESlateVisibility::Hidden);*/

	switch (Target)
	{
	case ESettingCategory::Screen:
		UI_Screen->SetVisibility(ESlateVisibility::Visible);
		break;

	case ESettingCategory::Grapic:
		UI_Grapic->SetVisibility(ESlateVisibility::Visible);
		break;

	/*case ESettingCategory::Sound:
		UI_Sound->SetVisibility(ESlateVisibility::Visible);
		break;

	case ESettingCategory::Control:
		UI_Control->SetVisibility(ESlateVisibility::Visible);
		break;

	case ESettingCategory::Gameplay:
		UI_Gameplay->SetVisibility(ESlateVisibility::Visible);
		break;

	case ESettingCategory::System:
		UI_System->SetVisibility(ESlateVisibility::Visible);
		break;*/
	}
}

#pragma endregion

#pragma region Gear

void UUI_PopUp_Setting::RotateGear(float TargetAngle)
{
	const float AddAngle = GetShortestAddAngle(CurrentAngle, TargetAngle);
	const float FinalAngle = CurrentAngle + AddAngle;

	const float DeltaSeconds = GetWorld()->GetDeltaSeconds();
	const float RotateSpeed = 90.f;

	GetWorld()->GetTimerManager().SetTimer(AngleHandle, FTimerDelegate::CreateWeakLambda(this, [this, FinalAngle, DeltaSeconds, RotateSpeed]()
		{
			FWidgetTransform TargetTrans;
			CurrentAngle = FMath::FInterpConstantTo(CurrentAngle, FinalAngle, DeltaSeconds, RotateSpeed);
			TargetTrans.Angle = CurrentAngle;

			UI_Gear->SetRenderTransform(TargetTrans);

			if (FMath::IsNearlyEqual(CurrentAngle, FinalAngle))
			{
				CurrentAngle = FinalAngle;
				TargetTrans.Angle = CurrentAngle;
				UI_Gear->SetRenderTransform(TargetTrans);

				GetWorld()->GetTimerManager().ClearTimer(AngleHandle);
			}
		}), DeltaSeconds, true);
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
	UGameUserSettings::GetGameUserSettings()->ApplySettings(false);

	Input_ESC();
}

#pragma endregion