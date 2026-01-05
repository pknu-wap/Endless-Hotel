// Copyright by 2025-2 WAP Game 2 team

#include "UI/Slider/Custom/UI_Slider_Custom.h"
#include <Components/Slider.h>
#include <Components/ProgressBar.h>

#pragma region Base

void UUI_Slider_Custom::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Slider_Main->OnValueChanged.AddDynamic(this, &ThisClass::Slide_Slider);
}

#pragma endregion

#pragma region Slide

void UUI_Slider_Custom::Slide_Slider(float Value)
{
	ProgressBar_Left->SetPercent(Value);
}

#pragma endregion