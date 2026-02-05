// Copyright by 2025-2 WAP Game 2 team

#include "UI/Slider/UI_Slider_Base.h"
#include <Components/Slider.h>
#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>

#pragma region Base

void UUI_Slider_Base::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Slider_Default->OnValueChanged.AddDynamic(this, &ThisClass::Slide_Slider);
}

#pragma endregion

#pragma region Slider

void UUI_Slider_Base::Slide_Slider(float Value)
{
	Slider_Default->SetValue(Value);
	ProgressBar_Left->SetPercent(Value);
	Text_Value->SetText(FText::FromString(FString::FromInt(Value * 100)));
}

#pragma endregion