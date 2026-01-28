// Copyright by 2025-2 WAP Game 2 team

#include "UI/Slider/Setting/UI_Slider_Setting.h"
#include "Player/Controller/EHPlayerController.h"
#include <Sound/SoundClass.h>
#include <Kismet/GameplayStatics.h>

#pragma region Slider

void UUI_Slider_Setting::Slide_Slider(float Value)
{
	Super::Slide_Slider(Value);

	switch (SettingCategory)
	{
	case ESettingCategory::Sound:
		SC_Target->Properties.Volume = Value;
		break;

	case ESettingCategory::Control:
		auto* PC = Cast<AEHPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (!PC) break; // 메인 메뉴의 경우 PC가 없음
		PC->SetLookSensitivity(Value);
		break;
	}
}

#pragma endregion