// Copyright by 2025-2 WAP Game 2 team

#include "UI/Slider/Setting/UI_Slider_Setting.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/HUD/InGame/UI_HUD_InGame.h"
#include "UI/CheckBox/Setting/UI_CheckBox_Setting.h"
#include "UI/PopUp/Setting/UI_PopUp_Setting.h"
#include "UI/PopUp/Setting/UI_PopUp_Option.h"
#include "Player/Controller/EHPlayerController.h"
#include "Sound/SoundController.h"
#include <Sound/SoundClass.h>
#include <Kismet/GameplayStatics.h>
#include <Components/Image.h>
#include <Components/TextBlock.h>

#pragma region Base

void UUI_Slider_Setting::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CheckBox_Off->OnCheckStateChanged.AddDynamic(this, &ThisClass::Click_CheckBox);
}

#pragma endregion

#pragma region Slider

void UUI_Slider_Setting::Slide_Slider(float Value)
{
	Super::Slide_Slider(Value);

	Text_Value->SetText(FText::FromString(FString::FromInt(Value * 100)));

	auto* UI_Setting = GetTypedOuter<UUI_PopUp_Setting>();
	FSaveData_Setting& Data = UI_Setting->Data_Setting;

	auto* SoundCon = GetGameInstance()->GetSubsystem<USoundController>();

	switch (OptionCategory)
	{
	case EOptionCategory::Master:
		Data.Master = Value;
		SoundCon->SetSoundClassValue(ESoundClassType::Master, Value * Data.EnableMaster);
		break;

	case EOptionCategory::BGM:
		Data.BGM = Value;
		SoundCon->SetSoundClassValue(ESoundClassType::Master, Value * Data.EnableBGM);
		break;

	case EOptionCategory::SFX:
		Data.SFX = Value;
		SoundCon->SetSoundClassValue(ESoundClassType::Master, Value * Data.EnableSFX);
		break;

	case EOptionCategory::Voice:
		Data.Voice = Value;
		SoundCon->SetSoundClassValue(ESoundClassType::Master, Value * Data.EnableVoice);
		break;

	case EOptionCategory::Interface:
		Data.Interface = Value;
		SoundCon->SetSoundClassValue(ESoundClassType::Master, Value * Data.EnableInterface);
		break;

	case EOptionCategory::Sensitivity:
	{
		auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (!PC) break; // 메인 메뉴의 경우 PC가 없음
		PC->SetLookSensitivity(Value);

		Data.Sensitivity = Value;
		break;
	}

	case EOptionCategory::Brightness:
	{
		auto* UI_Option = GetTypedOuter<UUI_PopUp_Option>();
		UImage* Image_Brightness = Cast<UImage>(UI_Option->GetWidgetFromName(TEXT("Image_Brightness")));
		FLinearColor Color = Image_Brightness->GetColorAndOpacity();
		float AlphaValue = 0.05f + Value * 0.95f;

		Color.A = AlphaValue;
		Image_Brightness->SetColorAndOpacity(Color);

		auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
		if (auto* UI_InGame = Cast<UUI_HUD_InGame>(UICon->GetCurrentBaseWidget()))
		{
			UI_InGame->SetBrightness(AlphaValue);
		}

		Data.Brightness = Value;
		break;
	}
	}
}

#pragma endregion

#pragma region CheckBox

void UUI_Slider_Setting::Click_CheckBox(bool bIsCheck)
{
	ShowOffImage(bIsCheck);

	auto* UI_Setting = GetTypedOuter<UUI_PopUp_Setting>();
	FSaveData_Setting& Data = UI_Setting->Data_Setting;

	auto* SoundCon = GetGameInstance()->GetSubsystem<USoundController>();

	switch (OptionCategory)
	{
	case EOptionCategory::Master:
	{
		if (bIsCheck)
		{
			Data.EnableMaster = 1;
			SoundCon->SetSoundClassValue(ESoundClassType::Master, Data.Master);
		}
		else
		{
			Data.EnableMaster = 0;
			SoundCon->SetSoundClassValue(ESoundClassType::Master, 0);
		}
		break;
	}

	case EOptionCategory::BGM:
	{
		if (bIsCheck)
		{
			Data.EnableBGM = 1;
			SoundCon->SetSoundClassValue(ESoundClassType::BGM, Data.BGM);
		}
		else
		{
			Data.EnableBGM = 0;
			SoundCon->SetSoundClassValue(ESoundClassType::BGM, 0);
		}
		break;
	}

	case EOptionCategory::SFX:
	{
		if (bIsCheck)
		{
			Data.EnableSFX = 1;
			SoundCon->SetSoundClassValue(ESoundClassType::SFX, Data.SFX);
		}
		else
		{
			Data.EnableSFX = 0;
			SoundCon->SetSoundClassValue(ESoundClassType::SFX, 0);
		}
		break;
	}

	case EOptionCategory::Voice:
	{
		if (bIsCheck)
		{
			Data.EnableVoice = 1;
			SoundCon->SetSoundClassValue(ESoundClassType::Voice, Data.Voice);
		}
		else
		{
			Data.EnableVoice = 0;
			SoundCon->SetSoundClassValue(ESoundClassType::Voice, 0);
		}
		break;
	}

	case EOptionCategory::Interface:
	{
		if (bIsCheck)
		{
			Data.EnableInterface = 1;
			SoundCon->SetSoundClassValue(ESoundClassType::UI, Data.Interface);
		}
		else
		{
			Data.EnableInterface = 0;
			SoundCon->SetSoundClassValue(ESoundClassType::UI, 0);
		}
		break;
	}
	}
}

void UUI_Slider_Setting::ShowOffImage(bool bIsCheck)
{
	if (bIsCheck)
	{
		Image_Off->SetVisibility(ESlateVisibility::Hidden);
		CheckBox_Off->SetCheckedState(ECheckBoxState::Checked);
	}
	else
	{
		Image_Off->SetVisibility(ESlateVisibility::Visible);
		CheckBox_Off->SetCheckedState(ECheckBoxState::Unchecked);
	}
}

#pragma endregion