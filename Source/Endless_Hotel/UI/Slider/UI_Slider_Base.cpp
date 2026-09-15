// Copyright by 2025-2 WAP Game 2 team

#include "UI/Slider/UI_Slider_Base.h"
#include <Components/ProgressBar.h>

#pragma region Base

void UUI_Slider_Base::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Slider->OnValueChanged.AddDynamic(this, &ThisClass::Slide_Slider);
}

#pragma endregion

#pragma region Slider

void UUI_Slider_Base::Slide_Slider(float Value)
{
	Slider->SetValue(Value);
	ProgressBar->SetPercent(Value);
}

#pragma endregion