// Copyright by 2025-2 WAP Game 2 team

#include "UI/PopUp/Setting/UI_PopUp_Option.h"
#include "UI/PopUp/Setting/UI_PopUp_Setting.h"
#include "UI/ComboBox/Setting/UI_ComboBox_Setting.h"
#include "UI/Button/Setting/UI_Button_Option.h"
#include "UI/Slider/Setting/UI_Slider_Setting.h"
#include "GameSystem/SaveGame/SaveManager.h"
#include <Blueprint/WidgetTree.h>

#pragma region Base

void UUI_PopUp_Option::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ComboBox_Default = Cast<UUI_ComboBox_Setting>(GetWidgetFromName(TEXT("ComboBox")));

	if (ComboBox_Default)
	{
		ComboBox_Default->ClearOptions();

		for (auto Value : ComboBoxOptions)
		{
			ComboBox_Default->AddEnumOption<EOptionValue>(Value);
		}
	}
}

void UUI_PopUp_Option::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (ComboBox_Default)
	{
		ComboBox_Default->BindEvents();
	}
}

#pragma endregion

#pragma region Highlight

void UUI_PopUp_Option::HighlightOptions()
{
	FSaveData_Setting Data = USaveManager::LoadSettingData();
	UEnum* EnumObj = StaticEnum<EOptionValue>();

	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(OUT Widgets);

	for (auto* Child : Widgets)
	{
		if (auto* Target = Cast<UUI_ComboBox_Setting>(Child))
		{
			EOptionValue Value;

			switch (Target->OptionCategory)
			{
			case EOptionCategory::Resolution:
				Value = Data.Resolution;
				break;

			case EOptionCategory::Grapic:
				Value = Data.Grapic;
				break;

			case EOptionCategory::Language:
				Value = Data.Language;
				break;
			}

			Target->SetSelectedOption(EnumObj->GetNameByValue(static_cast<int64>(Value)));
		}

		if (auto* Target = Cast<UUI_Button_Option>(Child))
		{
			FOptionInfo OptionInfo = Target->OptionInfo;

			switch (OptionInfo.Category)
			{
			case EOptionCategory::Window:
				OptionInfo.Value = Data.Window;
				break;

			case EOptionCategory::Aspect:
				OptionInfo.Value = Data.Aspect;
				break;

			case EOptionCategory::Frame:
				OptionInfo.Value = Data.Frame;
				break;

			case EOptionCategory::VSync:
				OptionInfo.Value = Data.VSync;
				break;

			case EOptionCategory::HDR:
				OptionInfo.Value = Data.HDR;
				break;

			case EOptionCategory::AntiAliasing:
				OptionInfo.Value = Data.AntiAliasing;
				break;

			case EOptionCategory::Shadow:
				OptionInfo.Value = Data.Shadow;
				break;

			case EOptionCategory::Texture:
				OptionInfo.Value = Data.Texture;
				break;

			case EOptionCategory::PostProcessing:
				OptionInfo.Value = Data.PostProcessing;
				break;

			case EOptionCategory::Shading:
				OptionInfo.Value = Data.Shading;
				break;

			case EOptionCategory::Overlap:
				OptionInfo.Value = Data.Overlap;
				break;
			}

			Target->HighlightOption.Broadcast(OptionInfo);
		}

		if (auto* Target = Cast<UUI_Slider_Setting>(Child))
		{
			float TargetValue = 0;

			switch (Target->OptionCategory)
			{
			case EOptionCategory::Master:
				TargetValue = Data.Master;
				Target->ShowOffImage(static_cast<bool>(Data.EnableMaster));
				break;

			case EOptionCategory::BGM:
				TargetValue = Data.BGM;
				Target->ShowOffImage(static_cast<bool>(Data.EnableBGM));
				break;

			case EOptionCategory::SFX:
				TargetValue = Data.SFX;
				Target->ShowOffImage(static_cast<bool>(Data.EnableSFX));
				break;

			case EOptionCategory::Voice:
				TargetValue = Data.Voice;
				Target->ShowOffImage(static_cast<bool>(Data.EnableVoice));
				break;

			case EOptionCategory::Interface:
				TargetValue = Data.Interface;
				Target->ShowOffImage(static_cast<bool>(Data.EnableInterface));
				break;

			case EOptionCategory::Sensitivity:
				TargetValue = Data.Sensitivity;
				break;

			case EOptionCategory::Brightness:
				TargetValue = Data.Brightness;
				break;
			}

			Target->Slide_Slider(TargetValue);
		}
	}
}

#pragma endregion