// Copyright by 2025-2 WAP Game 2 team

#include "UI/Slider/Setting/UI_Slider_Setting.h"
#include "Sound/SoundClass.h"

#pragma region Slider

void UUI_Slider_Setting::Slide_Slider(float Value)
{
	Super::Slide_Slider(Value);

	SC_Target->Properties.Volume = Value;
}

#pragma endregion