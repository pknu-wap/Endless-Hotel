// Copyright by 2025-2 WAP Game 2 team

#include "UI/Slider/Setting/UI_Slider_Setting.h"
#include "UI/Controller/UI_Controller.h"
#include "UI/HUD/InGame/UI_InGame.h"
#include "Player/Controller/EHPlayerController.h"
#include <Sound/SoundClass.h>
#include <Kismet/GameplayStatics.h>
#include <Components/Image.h>

#pragma region Slider

void UUI_Slider_Setting::Slide_Slider(float Value)
{
	Super::Slide_Slider(Value);

	switch (OptionCategory)
	{
	case EOptionCategory::Master:
	case EOptionCategory::BGM:
	case EOptionCategory::SFX:
	case EOptionCategory::Voice:
	case EOptionCategory::Interface:
	{
		SC_Target->Properties.Volume = Value;
		break;
	}

	case EOptionCategory::Sensitivity:
	{
		auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (!PC) break; // 메인 메뉴의 경우 PC가 없음
		PC->SetLookSensitivity(Value);
		break;
	}

	case EOptionCategory::Brightness:
	{
		UImage* Image_Brightness = Cast<UImage>(Owner->GetWidgetFromName(TEXT("Image_Brightness")));
		FLinearColor Color = Image_Brightness->GetColorAndOpacity();
		float AlphaValue = 0.05f + Value * 0.95f;

		Color.A = AlphaValue;
		Image_Brightness->SetColorAndOpacity(Color);

		auto* UICon = GetGameInstance()->GetSubsystem<UUI_Controller>();
		if (auto* UI_InGame = Cast<UUI_InGame>(UICon->GetCurrentBaseWidget()))
		{
			UI_InGame->SetBrightness(AlphaValue);
		}

		break;
	}
	}
}

#pragma endregion