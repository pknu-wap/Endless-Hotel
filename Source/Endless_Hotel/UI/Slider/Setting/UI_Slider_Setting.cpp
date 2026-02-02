// Copyright by 2025-2 WAP Game 2 team

#include "UI/Slider/Setting/UI_Slider_Setting.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/HUD/InGame/UI_InGame.h"
#include "UI/PopUp/Setting/UI_PopUp_Setting.h"
#include "UI/PopUp/Setting/UI_PopUp_Option.h"
#include "Player/Controller/EHPlayerController.h"
#include <Sound/SoundClass.h>
#include <Kismet/GameplayStatics.h>
#include <Components/Image.h>

#pragma region Slider

void UUI_Slider_Setting::Slide_Slider(float Value)
{
	Super::Slide_Slider(Value);

	auto* UI_Setting = GetTypedOuter<UUI_PopUp_Setting>();
	FSaveData_Setting& Data = UI_Setting->Data_Setting;

	switch (OptionCategory)
	{
	case EOptionCategory::Master:
		Data.Master = Value;
		break;

	case EOptionCategory::BGM:
		Data.BGM = Value;
		break;

	case EOptionCategory::SFX:
		Data.SFX = Value;
		break;

	case EOptionCategory::Voice:
		Data.Voice = Value;
		break;

	case EOptionCategory::Interface:
		Data.Interface = Value;
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
		if (auto* UI_InGame = Cast<UUI_InGame>(UICon->GetCurrentBaseWidget()))
		{
			UI_InGame->SetBrightness(AlphaValue);
		}

		Data.Brightness = Value;
		break;
	}
	}

	if (SC_Target)
	{
		SC_Target->Properties.Volume = Value;
	}
}

#pragma endregion